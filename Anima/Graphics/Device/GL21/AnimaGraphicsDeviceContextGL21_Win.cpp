#include "../include/AnimaGraphicsDeviceContextGL21.h"
#include "../include/AnimaGraphicsDeviceDriverGL21.h"
#include "../include/AnimaGraphicsDeviceManagerGL21.h"
#include "../include/AnimaGraphicsDevicePipelineGL21.h"
#include "../include/AnimaGraphicsDeviceFrameBufferGL21.h"
#include "../include/AnimaGraphicsDevicePixelBufferDesc.h"
#include "../include/AnimaGraphicsDeviceStageInput2dGL21.h"

#include "../include/AnimaPlatform.h"

#include "../include/AnimaOSWindowWin.h"

#include <cassert>
#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ContextGL21::ContextGL21(AE::Graphics::Device::ContextDesc &contextDesc, AE::Graphics::Device::Driver *deviceDriver) 
				: Context(deviceDriver)
			{
				mDeviceContextHandle = ::GetDC(static_cast<AE::OS::WindowWin *>(contextDesc.parentWindow)->_getWindowHandle());

				AE::int8 redBits = 0, redShift = 0, greenBits = 0, greenShift = 0, blueBits = 0, blueShift = 0, alphaBits = 0, alphaShift = 0;
				AE::Graphics::ColorFormat colorFormat = contextDesc.getColorFormat();
				switch(colorFormat)
				{
					case CF_A8R8G8B8:
						redBits = 8; redShift = 0;
						greenBits = 8; greenShift = 8;
						blueBits = 8; blueShift = 16;
						alphaBits = 8; alphaShift = 24;
						break;
					case CF_X8R8G8B8:
						redBits = 8; redShift = 0;
						greenBits = 8; greenShift = 8;
						blueBits = 8; blueShift = 16;
						alphaBits = 0; alphaShift = 0;
						break;
					case CF_R8G8B8A8:
						redBits = 8; redShift = 16;
						greenBits = 8; greenShift = 8;
						blueBits = 8; blueShift = 0;
						alphaBits = 8; alphaShift = 24;
						break;
					case CF_R8G8B8X8:
						redBits = 8; redShift = 16;
						greenBits = 8; greenShift = 8;
						blueBits = 8; blueShift = 0;
						alphaBits = 0; alphaShift = 0;
						break;
					case CF_A1R5G5B5:
						redBits = 5; redShift = 0;
						greenBits = 5; greenShift = 5;
						blueBits = 5; blueShift = 10;
						alphaBits = 1; alphaShift = 15;
						break;
					case CF_X1R5G5B5:
						redBits = 5; redShift = 0;
						greenBits = 5; greenShift = 5;
						blueBits = 5; blueShift = 10;
						alphaBits = 0; alphaShift = 0;
						break;
					case CF_R5G6B5:
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
					contextDesc.getColorDepth(), // color depth  
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
				iPixelFormat = ::ChoosePixelFormat(mDeviceContextHandle, &pfd); 
				 
				// make it the pixel format of the device context  
				if(::SetPixelFormat(mDeviceContextHandle, iPixelFormat, &pfd) == FALSE)
					assert(false);

				// Create a rendering context  
				mRenderingContext = ::wglCreateContext(mDeviceContextHandle);
				
				if(mRenderingContext == NULL)
					assert(false);

				// Make it the calling thread's current rendering context
				BOOL result = ::wglMakeCurrent(mDeviceContextHandle, mRenderingContext);
				assert(result);

				// TODO EBD: This is wrong; isFullScreen() should belong to the device context
				if(contextDesc.parentWindow->isFullScreen())
				{
					DEVMODE dm;
					dm.dmSize = sizeof(DEVMODE);
					dm.dmPelsWidth = contextDesc.parentWindow->getDimensions().x;
					dm.dmPelsHeight = contextDesc.parentWindow->getDimensions().y;
					dm.dmBitsPerPel = contextDesc.getColorDepth();
					dm.dmDisplayFrequency = 60;
					dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;
					ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
				}

				//static_cast<AE::Graphics::Device::ManagerGL21 *>(AE::Graphics::Device::Manager::getInstance())->_initializeExtensions();
				GLenum error = glewInit();
				assert(error == GLEW_OK);

				glEnable(GL_TEXTURE_2D);

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				glPixelStorei(GL_PACK_ALIGNMENT, 1);

				AE::Graphics::Device::PixelBufferDesc pixelBufferDesc;
				
				// TODO Enabling video memory allocation
				pixelBufferDesc.allocationType = AE::Graphics::AT_SYSTEM_MEMORY;
				pixelBufferDesc.colorBufferDesc.colorFormat = pixelBufferDesc.colorFormatConversion = colorFormat;
				pixelBufferDesc.colorBufferDesc.data = 0;
				pixelBufferDesc.colorBufferDesc.dimensions = contextDesc.parentWindow->getDimensions();
				pixelBufferDesc.usage = AE::Graphics::Device::BU_DYNAMIC_WRITE;
				pixelBufferDesc.usesColorKey = false;

				mFrameBuffer = new AE::Graphics::Device::FrameBufferGL21(pixelBufferDesc);

				// Pipeline creation
				mPipeline = new AE::Graphics::Device::PipelineGL21(this);
				AE::Graphics::Device::SubpipelinePtr subpipeline2d = mPipeline->createSourceSubpipeline(AE::Graphics::Device::SPLT_2D_OPERATIONS);
				AE::Graphics::Device::SubpipelinePtr subpipeline3d = mPipeline->createSourceSubpipeline(AE::Graphics::Device::SPLT_3D_OPERATIONS);

				AE::Graphics::Device::SubpipelinePtr subpipelineRasterizer = subpipeline2d.get()->createSuccessor(AE::Graphics::Device::SPLT_RASTERIZER);
				subpipeline3d->connectTo(subpipelineRasterizer);

				AE::Graphics::Device::Stage *stageInput2d = subpipeline2d->createAndInsertStage(AE::Graphics::Device::ST_INPUT_2D, AE::NO_OPTIONS);
				AE::Graphics::Device::Stage *stageTransformation2d = subpipeline2d->createAndInsertStage(AE::Graphics::Device::ST_TRANSFORMATION_2D, AE::NO_OPTIONS);
				//AE::Graphics::Device::Stage *stageClipping = subpipeline2d->createAndInsertStage("Clipping2d", AE::Graphics::Device::ST_CLIPPING_2D);
				AE::Graphics::Device::Stage *stageRasterizer = subpipelineRasterizer->createAndInsertStage(AE::Graphics::Device::ST_RASTERIZER, AE::NO_OPTIONS);
				stageInput2d->setNextStage(stageTransformation2d);
				stageTransformation2d->setNextStage(stageRasterizer);
				// End of pipeline creation
			}

			ContextGL21::~ContextGL21()
			{
				// Resets the screen mode
				//ChangeDisplaySettings(0, 0);

				// Make the rendering context not current  
				::wglMakeCurrent(NULL, NULL);

				// Delete the rendering context  
				::wglDeleteContext(mRenderingContext);

				// Delete the window's device context
				::DeleteDC(mDeviceContextHandle);

				delete mFrameBuffer;

				delete mPipeline;
			}

			bool ContextGL21::beginRendering()
			{
				//AE::Graphics::Color backgroundColor = mViewport->getBackgroundColor();
				//glClearColor(backgroundColor.R / 255.0, backgroundColor.G / 255.0, backgroundColor.B / 255.0, 1.0f);
				glClearColor(0.0, 0.0, 0.0, 1.0);
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

			bool ContextGL21::beginRendering(const AE::Graphics::Color &clearColor)
			{
				//AE::Graphics::Color backgroundColor = mViewport->getBackgroundColor();
				glClearColor(clearColor.R / 255.0f, clearColor.G / 255.0f, clearColor.B / 255.0f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearDepth(1.0f);

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

				return true;
			}

			/*AE::Graphics::Surface* ContextGL21::createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory)
			{
				if(usesVideoMemory)
				{
					al_set_target_backbuffer(mAllegroDisplay);
					al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
				}
				else
					al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

				ALLEGRO_BITMAP *allegroSurface = al_create_bitmap(dimensions.x, dimensions.y);
				AE::Graphics::Surface *newSurface = new AE::Graphics::SurfaceAllegro(allegroSurface);

				return newSurface;
			}*/

			void ContextGL21::endRendering()
			{
				/*for(AE::uint i = 0; i < mWindows.size(); i++)
					mWindows[i]->render();*/

				//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
				/*glViewport(0, 0, mFrameBuffer->getDimensions().x, mFrameBuffer->getDimensions().y);

				// Reset the coordinate system before modifying

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				// Pseudo window coordinates
				gluOrtho2D(0.0, (GLfloat) mFrameBuffer->getDimensions().x, 0.0f, (GLfloat) mFrameBuffer->getDimensions().y);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();


				GLuint *pImage = (GLuint *)(malloc(sizeof(GLuint)));
				pImage[0] = 0xFFFF00FF;
				glRasterPos2i(50, 50);
				glDrawPixels(1, 1, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pImage);
				free(pImage);*/

				::SwapBuffers(mDeviceContextHandle);
			}

			void ContextGL21::render()
			{
			}
		}
	}
}