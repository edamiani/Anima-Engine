/*************************************************************************
 extensions.cpp
 
 Program to demonstrate the use of extensions.
 
 Author   :   Dave Astle
 Date     :   2/1/2002
*************************************************************************/

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
#include <cassert>
#include <cmath>
#include <cstdlib>

#include <gl/gl.h>
#include <gl/glu.h>

// if your compiler is complaining about not finding these headers, download
// them from the links in the article and copy them to your indlude directory
#include <gl/glext.h>
#include <gl/wglext.h>

#include "timer.h"


#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")

const int SCREEN_WIDTH =   800;
const int SCREEN_HEIGHT =  600;

const int COLOR_BITS =     32;
const int DEPTH_BITS =     24;
const int STENCIL_BITS =   8;
const int ACCUM_BITS =     0;

const bool  USE_FULLSCREEN  = false; 

const char* APP_TITLE       = "OpenGL Extensions Demo";
const char* WND_CLASS_NAME  = "My Window Class";

const int FPS_UPDATE_FREQUENCY = 200;

const float FOV = 45.0f;

const float PI = 3.14159265359f;
const float ROTATION_SPEED = PI / 2;


const float FLOOR_SIZE = 3.0;

void (APIENTRY * glCopyTexSubImage3DProc) (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);

// TGA-specific data structures
struct TGAHEADER
{
	BYTE idLength;
  BYTE colorMapType;
  BYTE imageType;
  BYTE colorMapSpec[5];
  WORD xOrigin;
  WORD yOrigin;
  WORD width;
  WORD height;
  BYTE bpp;
  BYTE imageDesc;
};

enum TGA_TYPES
{
  TGA_NODATA = 0,
  TGA_INDEXEDED = 1,
  TGA_RGB = 2,
  TGA_GRAYSCALE = 3,
  TGA_INDEXED_RLE = 9,
  TGA_RGB_RLE = 10,
  TGA_GRAYSCALE_RLE = 11
};



bool g_isActive;
bool g_isFullscreen;
HDC g_hdc;
HGLRC g_hrc;
HWND g_hwnd;
HINSTANCE g_hInstance;

GLuint g_floorTexture = 0;
GLuint g_lightmap = 0;

GLfloat g_lightPos[] = { 0.0f, 0.0f, 1.0f };



int g_screenWidth = SCREEN_WIDTH;
int g_screenHeight = SCREEN_HEIGHT;

bool g_useTextureCompression = false;
bool g_useEdgeClamp = false;
bool g_useSGISMipmapGeneration = false;

PFNGLMULTITEXCOORD2FARBPROC     pglMultiTexCoord2f     = NULL;
PFNGLCLIENTACTIVETEXTUREARBPROC	pglActiveTexture       = NULL;
PFNGLACTIVETEXTUREARBPROC       pglClientActiveTexture = NULL;
PFNGLPOINTPARAMETERFVEXTPROC    pglPointParameterfvEXT = NULL;
PFNWGLSWAPINTERVALEXTPROC       pwglSwapIntervalEXT    = NULL;


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
bool SetupWindow();
bool SetupPixelFormat();
bool KillWindow();
void ResizeScene(GLsizei width, GLsizei height);
void DisplayFPS(CTimer* pTimer);
bool GameInit();
bool GameMain(float elapsedTime);
bool GameCleanup();
bool InitializeExtensions();
bool CheckExtension(char* extensionName);
void DrawFloor(float elapsedTime);
void DrawLight(float elapsedTime);
bool LoadTGATexture(GLuint& textureID, char* filename, GLenum wrapMode);


/*************************************************************************
 WinMain()

 Windows entry point
*************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
  SetupWindow();

  MSG msg;
  int exitCode;
  CTimer timer;

  timer.Init();

  while (true)
  {
    if(PeekMessage(&msg, g_hwnd, NULL, NULL, PM_REMOVE))
    {
      if (msg.message == WM_QUIT)   // do we receive a WM_QUIT message?
      {
        exitCode = msg.wParam;
        break;              // if so, time to quit the application
      }
      else
      {
        TranslateMessage(&msg);     // translate and dispatch to event queue
        DispatchMessage(&msg);
      }
    }


    // don't update the scene if the app is minimized
    if (g_isActive)
    {
      // update the scene every time through the loop
      GameMain(timer.GetElapsedSeconds());

      DisplayFPS(&timer);

      // switch the front and back buffers to display the updated scene
      SwapBuffers(g_hdc);
    }
    else
    {
      timer.GetElapsedSeconds();
    }
  }

  KillWindow();

  return exitCode;
}


/*************************************************************************
 WndProc()

 Windows message handler
*************************************************************************/
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  switch(message)
  {
  case WM_CREATE:
    {
    } break;

  case WM_ACTIVATE:  // watch for the window being minimized and restored
    {
      if (!HIWORD(wParam))
      {
        // program was restored or maximized
        g_isActive = true;
      }
      else
      {
        // program was minimized
        g_isActive = false;
      }

      return 0;
    }

  case WM_SYSCOMMAND:  // look for screensavers and powersave mode
    {
      switch (wParam)
      {
      case SC_SCREENSAVE:     // screensaver trying to start
      case SC_MONITORPOWER:   // monitor going to powersave mode
        // returning 0 prevents either from happening
        return 0;
      default:
        break;
      }
    } break;

  case WM_CLOSE:    // window is being closed
    {
      // send WM_QUIT to message queue
      PostQuitMessage(0);

      return 0;
    }

  case WM_SIZE:
    {
      // update perspective with new width and height
      ResizeScene(LOWORD(lParam), HIWORD(lParam));
      return 0;
    }

  case WM_CHAR:
    {
      switch (toupper(wParam))
      {
      case VK_ESCAPE:
        {
          // send WM_QUIT to message queue
          PostQuitMessage(0);
          return 0;
        }
      default:
        break;
      };
    } break;

  case WM_PAINT:
    {
      PAINTSTRUCT ps;
      BeginPaint(hwnd, &ps);
      EndPaint(hwnd, &ps);
    } break;

  default:
    break;
  }

  return (DefWindowProc(hwnd, message, wParam, lParam));
} // end WndProc()



/*************************************************************************
 SetupWindow

 Create and show the window
*************************************************************************/
bool SetupWindow()
{
  // get our instance handle
  g_hInstance = GetModuleHandle(NULL);

  WNDCLASSEX  wc;    // window class

  // fill out the window class structure
  wc.cbSize         = sizeof(WNDCLASSEX);
  wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
  wc.lpfnWndProc    = WndProc;
  wc.cbClsExtra     = 0;
  wc.cbWndExtra     = 0;
  wc.hInstance      = g_hInstance;
  wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);  // default icon
  wc.hIconSm        = LoadIcon(NULL, IDI_WINLOGO);      // windows logo small icon
  wc.hCursor        = LoadCursor(NULL, IDC_ARROW);      // default arrow
  wc.hbrBackground  = NULL;     // no background needed
  wc.lpszMenuName   = NULL;     // no menu
  wc.lpszClassName  = WND_CLASS_NAME;
  
  // register the windows class
  if (!RegisterClassEx(&wc))
  {
    MessageBox(NULL,"Unable to register the window class", "Error", MB_OK | MB_ICONEXCLAMATION);

    // exit and return false
    return false;
  }

  DWORD dwExStyle;
  DWORD dwStyle;

  // set the window style appropriately, depending on whether we're in fullscreen mode
  if (g_isFullscreen)
  {
    dwExStyle = WS_EX_APPWINDOW;
    dwStyle = WS_POPUP;           // simple window with no borders or title bar
    ShowCursor(FALSE);            // hide the cursor for now
  }
  else
  {
    dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    dwStyle = WS_OVERLAPPEDWINDOW;
  }

  // set up the window we're rendering to so that the top left corner is at (0,0)
  // and the bottom right corner is (height,width)
  RECT  windowRect;
  windowRect.left = 0;
  windowRect.right = (LONG) g_screenWidth;
  windowRect.top = 0;
  windowRect.bottom = (LONG) g_screenHeight;

  // change the size of the rect to account for borders, etc. set by the style
  AdjustWindowRectEx(&windowRect, dwStyle, FALSE, dwExStyle);

  // class registered, so now create our window
  g_hwnd = CreateWindowEx(dwExStyle,          // extended style
                          WND_CLASS_NAME,     // class name
                          APP_TITLE,     // app name
                          dwStyle |           // window style
                          WS_CLIPCHILDREN |   // required for
                          WS_CLIPSIBLINGS,    // using OpenGL
                          0, 0,               // x,y coordinate
                          windowRect.right - windowRect.left, // width
                          windowRect.bottom - windowRect.top, // height
                          NULL,               // handle to parent
                          NULL,               // handle to menu
                          g_hInstance,        // application instance
                          NULL);              // no extra params

  // see if our window handle is valid
  if (!g_hwnd)
  {
    MessageBox(NULL, "Unable to create window", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // if we're in fullscreen mode, set the display up for it
  if (g_isFullscreen)
  {
    // set up the device mode structure
    DEVMODE screenSettings;
    memset(&screenSettings,0,sizeof(screenSettings));

    screenSettings.dmSize       = sizeof(screenSettings);
    screenSettings.dmPelsWidth  = g_screenWidth;  // screen width
    screenSettings.dmPelsHeight = g_screenHeight; // screen height
    screenSettings.dmBitsPerPel = COLOR_BITS;    // bits per pixel
    screenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

    // attempt to switch to the resolution and bit depth we've selected
    if (ChangeDisplaySettings(&screenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
      // if we can't get fullscreen, let them choose to quit or try windowed mode
      if (MessageBox(NULL, "Cannot run in the fullscreen mode at the selected resolution\n"
                           "on your video card. Try windowed mode instead?",
                           "glAucoma",
                           MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
      {
        g_isFullscreen = false;
      }
      else
      {
        return false;
      }
    }
  }

  // get a device context
  if (!(g_hdc = GetDC(g_hwnd)))
  {
    MessageBox(NULL,"Unable to create device context", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  if (!SetupPixelFormat())
    return false;

  // create the OpenGL rendering context
  if (!(g_hrc = wglCreateContext(g_hdc)))
  {
    MessageBox(NULL, "Unable to create OpenGL rendering context", "Error",MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // now make the rendering context the active one
  if(!wglMakeCurrent(g_hdc, g_hrc))
  {
    MessageBox(NULL,"Unable to activate OpenGL rendering context", "ERROR", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // show the window in the forground, and set the keyboard focus to it
  ShowWindow(g_hwnd, SW_SHOW);
  SetForegroundWindow(g_hwnd);
  SetFocus(g_hwnd);

  // set up the perspective for the current screen size
  ResizeScene(g_screenWidth, g_screenHeight);

  // do one-time initialization
  if (!GameInit())
  {
    MessageBox(NULL, "Initialization failed", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  return true;
} // end SetupWindow()



/*************************************************************************
 SetupPixelFormat()

 Sets up the pixel format according to the settings in settings.h
*************************************************************************/
bool SetupPixelFormat()
{
  // set the pixel format we want
  PIXELFORMATDESCRIPTOR pfd;
  
  memset (&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

  pfd.nSize =         sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion =      1;                    // default version
  pfd.dwFlags =       PFD_DRAW_TO_WINDOW |  // window drawing support
                      PFD_SUPPORT_OPENGL |  // OpenGL support
                      PFD_DOUBLEBUFFER;     // double buffering support
  pfd.iPixelType =    PFD_TYPE_RGBA;        // RGBA color mode
  pfd.cColorBits =    COLOR_BITS;           // color mode
  pfd.cDepthBits =    DEPTH_BITS;           // depth buffer size
  pfd.cStencilBits =  STENCIL_BITS;         // stencil buffer
  pfd.cAccumBits =    ACCUM_BITS;           // accumulation buffer
  pfd.iLayerType =    PFD_MAIN_PLANE;       // main drawing plane
      
  GLuint  pixelFormat;

  // find the closest available pixel format
  if (!(pixelFormat = ChoosePixelFormat(g_hdc, &pfd)))
  {
    MessageBox(NULL, "Can't find an appropriate pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  // set pixel format to device context
  if(!SetPixelFormat(g_hdc, pixelFormat, &pfd))
  {
    MessageBox(NULL, "Unable to set pixel format", "Error", MB_OK | MB_ICONEXCLAMATION);
    return false;
  }

  return true;
} // end SetupPixelFormat()


/*************************************************************************
 KillWindow()

 Deletes the DC, RC, and Window, and restores the original display.
*************************************************************************/
bool KillWindow()
{
  // call game-specific shutdown
  GameCleanup();
  
  // restore the original display if we're in fullscreen mode
  if (g_isFullscreen)
  {
    ChangeDisplaySettings(NULL, 0);
    ShowCursor(TRUE);
  }

  // if we have an RC, release it
  if (g_hrc)
  {
    // release the RC
    if (!wglMakeCurrent(NULL,NULL))
    {
      MessageBox(NULL, "Unable to release rendering context", "Error", MB_OK | MB_ICONINFORMATION);
    }

    // delete the RC
    if (!wglDeleteContext(g_hrc))
    {
      MessageBox(NULL, "Unable to delete rendering context", "Error", MB_OK | MB_ICONINFORMATION);
    }

    g_hrc = NULL;
  }

  // release the DC if we have one
  if (g_hdc && !ReleaseDC(g_hwnd, g_hdc))
  {
    MessageBox(NULL, "Unable to release device context", "Error", MB_OK | MB_ICONINFORMATION);
    g_hdc = NULL;
  }

  // destroy the window if we have a valid handle
  if (g_hwnd && !DestroyWindow(g_hwnd))
  {
    MessageBox(NULL, "Unable to destroy window", "Error", MB_OK | MB_ICONINFORMATION);
    g_hwnd = NULL;
  }

  // unregister our class so we can create a new one if we need to
  if (!UnregisterClass(WND_CLASS_NAME, g_hInstance))
  {
    MessageBox(NULL, "Unable to unregister window class", "Error", MB_OK | MB_ICONINFORMATION);
    g_hInstance = NULL;
  }

  return true;
} // end KillWindow()


/*************************************************************************
 ResizeScene()

 Called once when the application starts and again every time the window
 is resized by the user. This method should be overridden if an
 orthographic projection is desired.
*************************************************************************/
void ResizeScene(GLsizei width, GLsizei height)
{
  // avoid divide by zero
  if (height==0)  
  {
    height=1;
  }

  // save these new values
  g_screenWidth = width;
  g_screenHeight = height;

  // set the viewport to the new dimensions
  glViewport(0, 0, width, height);

  // select the projection matrix and clear it out
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // set the perspective with the appropriate aspect ratio
  gluPerspective(FOV, (GLfloat)width/(GLfloat)height, 0.1f, 1000.0f);

  // select modelview matrix
  glMatrixMode(GL_MODELVIEW);
} // end ResizeScene()


/*************************************************************************
 DisplayFPS()

 Determines the FPS, and displays it in the title bar (if we're in
 windowed mode) or on the screen (in fullscreen mode). The FPS is
 determined every FPS_UPDATE_FREQUENCY frames.
*************************************************************************/
void DisplayFPS(CTimer* pTimer)
{
  static int frameCount = 0;

  if (++frameCount == FPS_UPDATE_FREQUENCY)
  {
    if (g_isFullscreen)
    {
    }
    else
    {
      static char fps[1000];

      sprintf(fps, "%.0f fps, %s, %s, %s", pTimer->GetFPS(frameCount), glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));
      SetWindowText(g_hwnd, fps);
    }

    frameCount = 0;
  }
} // end DisplayFPS()


/*************************************************************************
 GameInit()

 Performs one-time game-specific setup. Returns false on any failure.
*************************************************************************/
bool GameInit()
{
  if (!InitializeExtensions())
    return false;

  // disable VSYNCH if possible
  if (pwglSwapIntervalEXT)
  {
    pwglSwapIntervalEXT(0);
  }

  glEnable(GL_DEPTH_TEST);

  LoadTGATexture(g_floorTexture, "floor.tga", GL_REPEAT);
  LoadTGATexture(g_lightmap, "lightmap.tga", (g_useEdgeClamp ? GL_CLAMP_TO_EDGE : GL_CLAMP));

  // set up the settings needed to render the light as a point
  glPointSize(12.0);
  glEnable(GL_POINT_SMOOTH);
  glHint(GL_POINT_SMOOTH, GL_NICEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // vary the light point size by the distance from the camera if possible
  if (pglPointParameterfvEXT)
  {
    GLfloat attenuation[3] = { 0.0, 0.5, 0.0 };
    pglPointParameterfvEXT(GL_DISTANCE_ATTENUATION_EXT, attenuation);
  }

  return true;
} // end GameInit()


/*************************************************************************
 GameMain()

 The work of the application is done here. This is called every frame.
*************************************************************************/
bool GameMain(float elapsedTime)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  gluLookAt(2.0, 1.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  DrawLight(elapsedTime);
  DrawFloor(elapsedTime);
  return true;
} // end GameMain()


/*************************************************************************
 GameCleanup()

 Called at the end of successful program execution.
*************************************************************************/
bool GameCleanup()
{
  if (g_floorTexture)
    glDeleteTextures(0, &g_floorTexture);

  if (g_lightmap)
    glDeleteTextures(0, &g_lightmap);

  return true;
} // end GameCleanup()


/*************************************************************************
 InitializeExtensions()

 Sets up all of the extensions needed. Returns false if a required
 extension isn't supported.
*************************************************************************/
bool InitializeExtensions()
{
  if (CheckExtension("GL_ARB_multitexture"))
  {
    pglMultiTexCoord2f = (PFNGLMULTITEXCOORD2FARBPROC) wglGetProcAddress("glMultiTexCoord2f");
	  pglActiveTexture = (PFNGLCLIENTACTIVETEXTUREARBPROC) wglGetProcAddress("glActiveTexture");
    pglClientActiveTexture = (PFNGLACTIVETEXTUREARBPROC) wglGetProcAddress("glClientActiveTexture");
  }
  else
  {
    MessageBox(g_hwnd, "This program requires multitexturing, which is not supported by your hardware", "ERROR", MB_OK);
    return false;
  }

  if (CheckExtension("GL_EXT_point_parameters"))
  {
    pglPointParameterfvEXT = (PFNGLPOINTPARAMETERFVEXTPROC) wglGetProcAddress("glPointParameterfvEXT");
  }

  if (CheckExtension("WGL_EXT_swap_control"))
  {
    pwglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC) wglGetProcAddress("wglSwapIntervalEXT");
  }

  if (!CheckExtension("GL_EXT_bgra"))
  {
    MessageBox(g_hwnd, "This program requires the BGRA pixel storage format, which is not supported by your hardware", "ERROR", MB_OK);
    return false;
  }

  g_useTextureCompression = CheckExtension("GL_ARB_texture_compression");
  g_useEdgeClamp = CheckExtension("GL_EXT_texture_edge_clamp");
  g_useSGISMipmapGeneration = CheckExtension("GL_SGIS_generate_mipmap");

  return true;
} // end InitializeExtensions()


/*************************************************************************
 CheckExtension()

 Returns true if the extension corresponding to extensionName exists.
*************************************************************************/
bool CheckExtension(char* extensionName)
{
  // get the list of supported extensions
  char* extensionList = (char*) glGetString(GL_EXTENSIONS);

  if (!extensionName || !extensionList)
    return false;

  while (*extensionList)
  {
    // find the length of the first extension substring
    unsigned int firstExtensionLength = strcspn(extensionList, " ");


    if (strlen(extensionName) == firstExtensionLength &&
        strncmp(extensionName, extensionList, firstExtensionLength) == 0)
    {
      return true;
    }

    // move to the next substring
    extensionList += firstExtensionLength + 1;
  }

  return false;
} // end CheckExtension()


/*************************************************************************
 DrawFloor()

 Renders the floor as a single quad with two textures.
*************************************************************************/
void DrawFloor(float elapsedTime)
{
  // determine the corner of the lightmap's position
  float texOriginU = -g_lightPos[0] + 0.5f - FLOOR_SIZE/2;
  float texOriginV = g_lightPos[2] + 0.5f - FLOOR_SIZE/2;

  // enable the second texture unit for the lightmap
	pglActiveTexture(GL_TEXTURE1_ARB); 
	glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, g_lightmap);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // enable the first texture unit for the brick texture
	pglActiveTexture(GL_TEXTURE0_ARB);
	glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, g_floorTexture);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  glColor3f(0.0, 0.0, 0.0);
  
  glBegin(GL_QUADS);
    pglMultiTexCoord2f(GL_TEXTURE0_ARB, 0.0, 0.0);
    pglMultiTexCoord2f(GL_TEXTURE1_ARB, texOriginU, texOriginV);
    glVertex3f(-FLOOR_SIZE/2, 0.0, FLOOR_SIZE/2);

    pglMultiTexCoord2f(GL_TEXTURE0_ARB, FLOOR_SIZE, 0.0);
    pglMultiTexCoord2f(GL_TEXTURE1_ARB, texOriginU + FLOOR_SIZE, texOriginV);
    glVertex3f(FLOOR_SIZE/2, 0.0, FLOOR_SIZE/2);

    pglMultiTexCoord2f(GL_TEXTURE0_ARB, FLOOR_SIZE, FLOOR_SIZE);
    pglMultiTexCoord2f(GL_TEXTURE1_ARB, texOriginU + FLOOR_SIZE, texOriginV + FLOOR_SIZE);
    glVertex3f(FLOOR_SIZE/2, 0.0, -FLOOR_SIZE/2);

    pglMultiTexCoord2f(GL_TEXTURE0_ARB, 0.0, FLOOR_SIZE);
    pglMultiTexCoord2f(GL_TEXTURE1_ARB, texOriginU, texOriginV + FLOOR_SIZE);
    glVertex3f(-FLOOR_SIZE/2, 0.0, -FLOOR_SIZE/2);
  glEnd();

  pglActiveTexture(GL_TEXTURE1_ARB);
  glDisable(GL_TEXTURE_2D);
  pglActiveTexture(GL_TEXTURE0_ARB);
  glDisable(GL_TEXTURE_2D);
} // end DrawFloor()


/*************************************************************************
 DrawLight()

 Render the light as a point primitive.
*************************************************************************/
void DrawLight(float elapsedTime)
{
  // update the light's position
  static float rads;
  rads += ROTATION_SPEED * elapsedTime;

  while (rads > 2 * PI)
    rads -= (2 * PI);

  g_lightPos[0] = sinf(rads) / 1.0f;
  g_lightPos[1] = 0.2f;
  g_lightPos[2] = cosf(rads) / 1.0f;

  glColor3f(1.0, 1.0, 0.8f);
  glEnable(GL_BLEND);
  glBegin(GL_POINTS);
    glVertex3fv(g_lightPos);
  glEnd();
  glDisable(GL_BLEND);
} // end DrawLight()


/*************************************************************************
 LoadTGATexture()

 Loads a Targa, extracts the data from it, and places it in a texture
 object associated with textureID.
*************************************************************************/
bool LoadTGATexture(GLuint& textureID, char* filename, GLenum wrapMode)
{
  // open the TGA file
  FILE* pFile = fopen(filename, "rb");
  if (!pFile)
    return false;
  
  // read in the image type
  TGAHEADER tga;
  fread(&tga, 1, sizeof(TGAHEADER), pFile);

  // see if the type is one that we support
  if ((tga.imageType != TGA_RGB) && (tga.imageType != TGA_GRAYSCALE))
  {
    fclose(pFile);
    return false;
  }

  // store texture information
  tga.width;
  tga.height;

  // if colorMode is 3, there is no alpha channel
  int colorMode = tga.bpp / 8;
  int imageSize = tga.width * tga.height * colorMode;

  // allocate memory for TGA image data
  LPBYTE pData = new BYTE[imageSize];
  
  // read image data
  fread(pData, 1, imageSize, pFile);
  
  // close the file
  fclose(pFile);

  // choose the proper data formats depending on whether or not there's an
  // alpha channel;
  GLenum dataFormat = colorMode == 3 ? GL_BGR_EXT : GL_BGRA_EXT;
  GLenum internalFormat;

  if (colorMode == 3)
  {
    if (g_useTextureCompression)
      internalFormat = GL_COMPRESSED_RGB_ARB;
    else
      internalFormat = GL_RGB;
  }
  else
  {
    if (g_useTextureCompression)
      internalFormat = GL_COMPRESSED_RGBA_ARB;
    else
      internalFormat = GL_RGBA;
  }

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);

  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

  // This is a terrible hack, but there seems to be an issue with using
  // the generate mipmap extension with texture compression on ATI cards
  if (g_useSGISMipmapGeneration && strncmp((char*)glGetString(GL_VENDOR), "ATI", 3) != 0)
  {
    glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, tga.width, tga.height, 0, dataFormat, GL_UNSIGNED_BYTE, pData);
  }
  else
  {
    gluBuild2DMipmaps(GL_TEXTURE_2D, internalFormat, tga.width, tga.height, dataFormat, GL_UNSIGNED_BYTE, pData);
  }

  delete [] pData;

  return true;
} // end LoadTGATexture()
