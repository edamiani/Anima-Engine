#include "../include/AnimaGraphicsCamera.h"
#include "../include/AnimaGraphicsDeviceContextGL.h"
#include "../include/AnimaGraphicsManagerGL.h"
#include "../include/AnimaGraphicsViewport.h"
#include "../include/AnimaOSWindow.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		DeviceContextGL::DeviceContextGL(AE::Graphics::Device *graphicsDevice) 
			: mGraphicsDevice(graphicsDevice)
		{
		}

		DeviceContextGL::~DeviceContextGL()
		{
		}

		AE::uint DeviceContextGL::createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat)
		{
			mWindows.push_back(window);

		#ifdef AE_PLATFORM_WIN32
			mDeviceContext = ::GetDC((HWND)window->getWindowHandle());

			AE::int8 redBits = 0, redShift = 0, greenBits = 0, greenShift = 0, blueBits = 0, blueShift = 0, alphaBits = 0, alphaShift = 0;
			switch(surfaceFormat)
			{
				case SF_A8R8G8B8:
					redBits = 8; redShift = 0;
					greenBits = 8; greenShift = 8;
					blueBits = 8; blueShift = 16;
					alphaBits = 8; alphaShift = 24;
					break;
				case SF_X8R8G8B8:
					redBits = 8; redShift = 0;
					greenBits = 8; greenShift = 8;
					blueBits = 8; blueShift = 16;
					alphaBits = 0; alphaShift = 0;
					break;
				case SF_A1R5G5B5:
					redBits = 5; redShift = 0;
					greenBits = 5; greenShift = 5;
					blueBits = 5; blueShift = 10;
					alphaBits = 1; alphaShift = 15;
					break;
				case SF_X1R5G5B5:
					redBits = 5; redShift = 0;
					greenBits = 5; greenShift = 5;
					blueBits = 5; blueShift = 10;
					alphaBits = 0; alphaShift = 0;
					break;
				case SF_R5G6B5:
					redBits = 5; redShift = 0;
					greenBits = 6; greenShift = 5;
					blueBits = 5; blueShift = 11;
					alphaBits = 0; alphaShift = 0;
					break;
			}

			PIXELFORMATDESCRIPTOR pfd = { 
				sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
				1,                     // version number  
				PFD_DRAW_TO_BITMAP |   // supports window  
				PFD_SUPPORT_OPENGL |   // supports OpenGL  
				PFD_DOUBLEBUFFER,      // double buffered  
				PFD_TYPE_RGBA,         // RGBA type  
				32,                    // 24-bit color depth  
				redBits, redShift,	   // Red bits, red shift
				greenBits, greenShift, // Green bits, green shift 
				blueBits, blueShift,   // Blue bits, blue shift
				alphaBits, alphaShift, // Alpha bits, alpha shift
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
			iPixelFormat = ::ChoosePixelFormat(mDeviceContext, &pfd); 
			 
			// make it the pixel format of the device context  
			if(::SetPixelFormat(mDeviceContext, iPixelFormat, &pfd) == FALSE)
				return false;

			// Create a rendering context  
			mRenderingContext = ::wglCreateContext(mDeviceContext);
			
			if(mRenderingContext == NULL)
				return false;

			// Make it the calling thread's current rendering context
			BOOL result = ::wglMakeCurrent(mDeviceContext, mRenderingContext);
			assert(result);

			if(window->isFullScreen())
			{
				DEVMODE dm;
				dm.dmSize = sizeof(DEVMODE);
				dm.dmPelsWidth = window->getWindowMetrics().width;
				dm.dmPelsHeight = window->getWindowMetrics().height;
				dm.dmBitsPerPel = window->getWindowMetrics().getColorDepth();
				dm.dmDisplayFrequency = 60;
				dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
				ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
			}

		#elif defined(AE_PLATFORM_OSX)

			static GLint glAttributes[] = 
			{
				AGL_DOUBLEBUFFER,	GL_TRUE,
				AGL_RGBA,			GL_TRUE,
				AGL_DEPTH_SIZE,		16,
				AGL_NONE 
			};
			
			AGLPixelFormat openGLFormat = aglChoosePixelFormat(NULL, 0, glAttributes);
			if(openGLFormat == NULL)
				return false;
			
			mAGLContext = aglCreateContext(openGLFormat, NULL);
			if(mAGLContext == NULL)
				return false;
			
			aglDestroyPixelFormat(openGLFormat);
			
			WindowRef winRef = window->getWindowHandle();
			
			//aglSetWindowRef(mAGLContext, winRef);
			aglSetDrawable(mAGLContext, GetWindowPort(winRef));
			aglSetCurrentContext(mAGLContext);			
				
		#endif
			
			AE::Graphics::DrawingContextGL *drawingContextGL = new AE::Graphics::DrawingContextGL(this, window->getWindowMetrics(), surfaceFormat);
			mDrawingContexts.push_back(drawingContextGL);
			window->setDrawingContext(drawingContextGL);

			static_cast<AE::Graphics::ManagerGL *>(AE::Graphics::Manager::getInstance())->_initializeExtensions();

			return (mDrawingContexts.size() - 1);
		}

		AE::Graphics::Surface* DeviceContextGL::createOffscreenSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat)
		{
			AE::Graphics::Surface *surface = new AE::Graphics::SurfaceGL(width, height, surfaceFormat);
			return surface;
		}

		bool DeviceContextGL::beginRendering()
		{
			AE::Graphics::Color backgroundColor = mViewport->getBackgroundColor();
			glClearColor(backgroundColor.R / 255.0, backgroundColor.G / 255.0, backgroundColor.B / 255.0, 1.0f);
			glClearDepth(1.0f);

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glShadeModel(GL_SMOOTH);

			/*AE::Math::Matrix4 viewMatrix = mViewport->getCamera()->getViewMatrix();
			AE::Math::Matrix4 projectionMatrix = mViewport->getProjectionMatrix();

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//viewMatrix = parentTransformation * viewMatrix;
			//viewMatrix = viewMatrix.transpose();
		#if AE_DOUBLE_PRECISION
			glMultMatrixd(viewMatrix._m);
		#else
			glMultMatrixf(viewMatrix._m);
		#endif
			GLdouble viewMatrixGL[16];
			glGetDoublev(GL_MODELVIEW_MATRIX, viewMatrixGL);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			projectionMatrix = projectionMatrix.transpose();
		#if AE_DOUBLE_PRECISION
			glMultMatrixd(projectionMatrix._m);
		#else
			glMultMatrixf(projectionMatrix._m);
		#endif*/

			

			/*GLuint *pImage = (GLuint *)(malloc(sizeof(GLuint)));
			pImage[0] = 0xFFFFFFFF;
			glRasterPos2i(50, 50);
			glDrawPixels(1, 1, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pImage);
			free(pImage);*/

			return true;
		}

		void DeviceContextGL::endRendering()
		{
			for(AE::uint i = 0; i < mWindows.size(); i++)
				mWindows[i]->render();

		#ifdef AE_PLATFORM_WIN32
			::SwapBuffers(mDeviceContext);
		#endif
		}
	}
}