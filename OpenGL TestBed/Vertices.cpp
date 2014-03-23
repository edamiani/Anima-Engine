#ifdef WIN32

#include <windows.h>
#include <Wingdi.h>
#include <gl/GL.h>
#include <gl/glu.h>
#include "../Dependencies/gl/glext.h"
#include "../Dependencies/gl/wglext.h"

// GL_EXT_draw_range_elements (1.2)
PFNGLDRAWRANGEELEMENTSPROC		glDrawRangeElements;

// GL_EXT_multi_draw_arrays (1.4)
PFNGLMULTIDRAWARRAYSPROC		glMultiDrawArrays;
PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements;

// GL_ARB_multitexture (1.4)
PFNGLCLIENTACTIVETEXTUREPROC	glClientActiveTexture;

// GL_ARB_vertex_buffer_object(1.5)
PFNGLBINDBUFFERPROC				glBindBuffer;
PFNGLBUFFERDATAPROC				glBufferData;
PFNGLBUFFERSUBDATAPROC			glBufferSubData;
PFNGLDELETEBUFFERSPROC			glDeleteBuffers;
PFNGLGENBUFFERSPROC				glGenBuffers;
PFNGLGETBUFFERPARAMETERIVPROC	glGetBufferParameteriv;
PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv;
PFNGLGETBUFFERSUBDATAPROC		glGetBufferSubData;
PFNGLISBUFFERPROC				glIsBuffer;
PFNGLMAPBUFFERPROC				glMapBuffer;
PFNGLUNMAPBUFFERPROC			glUnmapBuffer;

#include "AnimaMathVector3.h"

#define AE_GL_BUFFER_OFFSET(i) ((char*)NULL + (i))



static const GLsizeiptr PositionSize = 6 * 2 * sizeof(GLfloat);
static const GLfloat PositionData[] =
{
	-1.0f,-2.0f,
	 1.0f,-1.0f,
	 1.0f, 1.0f,
	 1.0f, 1.0f,
	-1.0f, 1.0f,
	-1.0f,-1.0f,
};

static const GLsizeiptr ColorSize = 6 * 3 * sizeof(GLubyte);
static const GLubyte ColorData[] =
{
	255,   0,   0,
	255, 255,   0,
	  0, 255,   0,
	  0, 255,   0,
	  0,   0, 255,
	255,   0,   0
};

static const int BufferSize = 2;
static GLuint BufferName[BufferSize];

static const GLsizei VertexCount = 6; 

enum
{
    POSITION_OBJECT = 0,
    COLOR_OBJECT = 1
};




bool _checkOpenGLExtension(char* extensionName)
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
}

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
HDC deviceContext;
HGLRC glRenderingContext;
GLuint bufferId = 0;
GLuint indexBufferId = 0;







bool InitGL(HWND hWnd)
{
	deviceContext = ::GetDC(hWnd);

    PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
		1,                     // version number  
		PFD_DRAW_TO_WINDOW |   // support window  
		PFD_SUPPORT_OPENGL |   // support OpenGL  
		PFD_DOUBLEBUFFER,      // double buffered  
		PFD_TYPE_RGBA,         // RGBA type  
		24,                    // 24-bit color depth  
		0, 0, 0, 0, 0, 0,      // color bits ignored  
		0,                     // no alpha buffer  
		0,                     // shift bit ignored  
		0,                     // no accumulation buffer  
		0, 0, 0, 0,            // accum bits ignored  
		32,                    // 32-bit z-buffer  
		0,                     // no stencil buffer  
		0,                     // no auxiliary buffer  
		PFD_MAIN_PLANE,        // main layer  
		0,                     // reserved  
		0, 0, 0                // layer masks ignored  
	};

	int iPixelFormat;

	// get the best available match of pixel format for the device context   
	iPixelFormat = ::ChoosePixelFormat(deviceContext, &pfd); 
	 
	// make that the pixel format of the device context  
	if(::SetPixelFormat(deviceContext, iPixelFormat, &pfd) == FALSE)
		return false;

	// Create a rendering context  
	glRenderingContext = ::wglCreateContext(deviceContext);
	
	if(glRenderingContext == NULL)
		return false;

	// Make it the calling thread's current rendering context
	::wglMakeCurrent(deviceContext, glRenderingContext);

	if(_checkOpenGLExtension("GL_EXT_draw_range_elements"))
	{
		glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC) wglGetProcAddress("glDrawRangeElementsEXT");
	}

	if(_checkOpenGLExtension("GL_EXT_multi_draw_arrays"))
	{
		glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC) wglGetProcAddress("glMultiDrawArraysEXT");
		glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC) wglGetProcAddress("glMultiDrawElementsEXT");
	}

	if(_checkOpenGLExtension("GL_ARB_multitexture"))
	{
		glClientActiveTexture = (PFNGLCLIENTACTIVETEXTUREPROC) wglGetProcAddress("glClientActiveTextureARB");
	}

	if(_checkOpenGLExtension("GL_ARB_vertex_buffer_object"))
	{
		glBindBuffer = (PFNGLBINDBUFFERPROC) wglGetProcAddress("glBindBufferARB");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC) wglGetProcAddress("glDeleteBuffersARB");
		glGenBuffers = (PFNGLGENBUFFERSPROC) wglGetProcAddress("glGenBuffersARB");
		glIsBuffer = (PFNGLISBUFFERPROC) wglGetProcAddress("glIsBufferARB");
		glBufferData = (PFNGLBUFFERDATAPROC) wglGetProcAddress("glBufferDataARB");
		glBufferSubData = (PFNGLBUFFERSUBDATAPROC) wglGetProcAddress("glBufferSubDataARB");
		glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC) wglGetProcAddress("glGetBufferSubDataARB");
		glMapBuffer = (PFNGLMAPBUFFERPROC) wglGetProcAddress("glMapBufferARB");
		glUnmapBuffer = (PFNGLUNMAPBUFFERPROC) wglGetProcAddress("glUnmapBufferARB");
		glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC) wglGetProcAddress("glGetBufferParameterivARB");
		glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC) wglGetProcAddress("glGetBufferPointervARB");
	}

	return true;
}



bool InitVB()
{
	// Allocate memory
	GLuint id[2];
	glGenBuffers(2, id);
	bufferId = id[0];
	indexBufferId = id[1];

	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

	AE::Math::Vector3 vertexPosition;
	std::vector<AE::Math::Vector3> positions;
	vertexPosition = AE::Math::Vector3( 0.0,  0.5, -1.0); positions.push_back(vertexPosition);
	vertexPosition = AE::Math::Vector3( -0.5, -0.5, -1.0); positions.push_back(vertexPosition);
	vertexPosition = AE::Math::Vector3( 0.5, -0.5, -1.0); positions.push_back(vertexPosition);

	DWORD color = 0x009999;
	std::vector<DWORD> diffuseColors;
	diffuseColors.push_back(0xff00ff00);
	diffuseColors.push_back(0x000000ff);
	diffuseColors.push_back(0xffffffff);

	//AE::uint strideInBytes = 11;
	AE::uint strideInBytes = 15;

	GLuint bufferUsageGL = GL_STATIC_DRAW;

	// Buffer filling process
	/*AE::uchar *pBytes = 0;
	AE::uchar *pTempBytes = 0;
	pBytes = (AE::uchar *)malloc(positions.size() * strideInBytes);
	pTempBytes = pBytes;*/
	GLsizeiptr size = positions.size() * strideInBytes;
	glBufferData(GL_ARRAY_BUFFER, size, 0, bufferUsageGL);
	AE::uchar *pBytes = (AE::uchar *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	//::ZeroMemory(pBytes, positions.size() * strideInBytes);
	{
		AE::uint sizeofFloat = sizeof(float);
		AE::uint sizeOfFloatTimesTwo = sizeofFloat * 2;
		AE::uint sizeOfFloatTimesThree = sizeofFloat * 3;
		AE::uint sizeofColor = 3 * sizeof(GLubyte);

		for(AE::uint i = 0; i < positions.size(); i++)
		{
			// Position
			/*memcpy(pTempBytes, &positions[i].x, sizeOfFloatTimesThree);
			pTempBytes += sizeOfFloatTimesThree;*/
			memcpy(pBytes, &positions[i].x, sizeOfFloatTimesThree);
			pBytes += sizeOfFloatTimesThree;

			// Diffuse color
			/*memcpy(pTempBytes, &diffuseColors[i], sizeofColor);
			pTempBytes += sizeofColor;*/
			memcpy(pBytes, &diffuseColors[i], sizeofColor);
			pBytes += sizeofColor;
		}
		glUnmapBuffer(GL_ARRAY_BUFFER);

		//GLsizeiptr size = positions.size() * strideInBytes;
		//glBufferData(GL_ARRAY_BUFFER, size, (void *)pBytes, bufferUsageGL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	std::vector<AE::uchar> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(2);

	/*AE::uchar *pIndices;
	pIndices = (AE::uchar *)malloc(indices.size() * sizeof(AE::uchar));
	AE::uchar *pTempIndices = pIndices;*/
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(AE::uchar), 0, bufferUsageGL);
	AE::uchar *pIndices = (AE::uchar *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	{
		for(AE::uint i = 0; i < indices.size(); i++)
			*pIndices++ = indices[i];

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
	}

	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(AE::uchar), (void *)pIndices, bufferUsageGL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenBuffers(BufferSize, BufferName);

	glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);
    glBufferData(GL_ARRAY_BUFFER, ColorSize, ColorData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);
    glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void Render()
{
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
	glClearDepth(1.0F);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	//gluLookAt(0, 0, 1, 0, 0, -5, 0, 1, 0);
    //glTranslatef(0.0f, 0.0f, -0.1f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(90.0f, 1.0, 0.1f, 100.0f);
	glFrustum(-1, 1, -1, 1, 0.95, 10);

	/*//glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glTranslatef(0.0f, 0.0f,-4.0f);
	gluLookAt(0, 0, 0, 0, 0, -5, 0, 1, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);*/

	



    /*glBindBuffer(GL_ARRAY_BUFFER, BufferName[COLOR_OBJECT]);
    glColorPointer(3, GL_UNSIGNED_BYTE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, BufferName[POSITION_OBJECT]);
    glVertexPointer(2, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_TRIANGLES, 0, VertexCount);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);*/




	//AE::uint strideInBytes = 11;
	AE::uint strideInBytes = 15;
	AE::uint sizeofFloat = sizeof(float);
	AE::uint sizeOfFloatTimesTwo = sizeofFloat * 2;
	AE::uint sizeOfFloatTimesThree = sizeofFloat * 3;

	glBindBuffer(GL_ARRAY_BUFFER, bufferId);
	//glVertexPointer(2, GL_FLOAT, strideInBytes, AE_GL_BUFFER_OFFSET(0));
	glVertexPointer(3, GL_FLOAT, strideInBytes, AE_GL_BUFFER_OFFSET(0));
	//glColorPointer(3, GL_UNSIGNED_BYTE, strideInBytes, AE_GL_BUFFER_OFFSET(sizeOfFloatTimesTwo));
	glColorPointer(3, GL_UNSIGNED_BYTE, strideInBytes, AE_GL_BUFFER_OFFSET(sizeOfFloatTimesThree));

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
	size_t error = glGetError();

	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, AE_GL_BUFFER_OFFSET(0));
	error = glGetError();

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);




	/*glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
		glVertex3f(0.25, 0.25, 0.0);
		glVertex3f(0.75, 0.25, 0.0);
		glVertex3f(0.75, 0.75, 0.0);
		glVertex3f(0.25, 0.75, 0.0);
	glEnd();*/



	//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glViewport(0, 0, 300, 300);

	// Reset the coordinate system before modifying

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Pseudo window coordinates
    gluOrtho2D(0.0, (GLfloat) 300, 0.0f, (GLfloat) 300);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


	GLuint *pImage = (GLuint *)(malloc(sizeof(GLuint)));
	pImage[0] = 0xFFFF00FF;
	glRasterPos2i(50, 50);
	glDrawPixels(1, 1, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pImage);
	free(pImage);




	::SwapBuffers(deviceContext);
}



void Cleanup()
{
    // Make the rendering context not current  
	::wglMakeCurrent(NULL, NULL);

	// Delete the rendering context  
	::wglDeleteContext(glRenderingContext);

	// Delete the window's device context
	::DeleteDC(deviceContext);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
        case WM_DESTROY:
            Cleanup();
            PostQuitMessage( 0 );
            return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        L"OpenGL TestBed", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( L"OpenGL TestBed", L"OpenGL TestBed",
                              WS_OVERLAPPEDWINDOW, 100, 100, 300, 300,
                              NULL, NULL, wc.hInstance, NULL );

    // Initialize Direct3D
    if(InitGL(hWnd))
    {
        // Create the vertex buffer
        if(InitVB())
        {
            // Show the window
            ShowWindow(hWnd, SW_SHOWDEFAULT);
            UpdateWindow(hWnd);

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof( msg ) );
            while( msg.message != WM_QUIT )
            {
                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
                {
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else
                    Render();
            }
        }
    }

    UnregisterClass( L"OpenGL TestBed", wc.hInstance );
    return 0;
}

#endif
