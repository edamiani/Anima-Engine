#include "../include/AnimaGraphicsDeviceContextGL1_5.h"
#include "../include/AnimaGraphicsDeviceDriverGL1_5.h"
#include "../include/AnimaGraphicsDeviceManagerGL1_5.h"
#include "../include/AnimaGraphicsSurfaceDesc.h"
#include "../include/AnimaGraphicsSurfaceFactory.h"
#include "../include/AnimaPlatform.h"

#include "../include/AnimaOSWindowCocoa.h"

#include <cassert>
#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ContextGL1_5::ContextGL1_5(AE::Graphics::Device::ContextDesc &contextDesc, AE::Graphics::Device::Driver *deviceDriver) 
				: Context(deviceDriver)
			{
				/*static GLint glAttributes[] = 
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
				aglSetCurrentContext(mAGLContext)*/

				static_cast<AE::Graphics::Device::ManagerGL1_5 *>(AE::Graphics::Device::Manager::getInstance())->_initializeExtensions();

				AE::Graphics::SurfaceDesc surfaceDesc;
				
				// TODO Enabling video memory allocation
				surfaceDesc.allocationType = AE::Graphics::AT_SYSTEM_MEMORY;
				surfaceDesc.dimensions = contextDesc.parentWindow->getDimensions();
				surfaceDesc.surfaceFormat = surfaceFormat;

				//mFrameBuffer = new AE::Graphics::SurfaceGL1_5(surfaceDesc);
				mFrameBuffer = AE::Graphics::Device::Manager::getInstance()->getSurfaceFactory()->createSurface(surfaceDesc);
				static_cast<AE::Graphics::SurfaceGL1_5 *>(mFrameBuffer)->_setOffScreen(false);
			}

			ContextGL1_5::~ContextGL1_5()
			{
			#ifdef AE_PLATFORM_WIN32
				// Resets the screen mode
				//ChangeDisplaySettings(0, 0);

				// Make the rendering context not current  
				::wglMakeCurrent(NULL, NULL);

				// Delete the rendering context  
				::wglDeleteContext(mRenderingContext);

				// Delete the window's device context
				::DeleteDC(mDeviceContextHandle);
			#endif
				AE::Graphics::Device::Manager::getInstance()->getSurfaceFactory()->destroySurface(mFrameBuffer);
			}

			bool ContextGL1_5::beginRendering()
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

			bool ContextGL1_5::beginRendering(const AE::Graphics::Color &clearColor)
			{
				//AE::Graphics::Color backgroundColor = mViewport->getBackgroundColor();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(clearColor.R / 255.0f, clearColor.G / 255.0f, clearColor.B / 255.0f, 1.0f);
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

			AE::Graphics::Surface* ContextGL1_5::createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory)
			{
				/*if(usesVideoMemory)
				{
					al_set_target_backbuffer(mAllegroDisplay);
					al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
				}
				else
					al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

				ALLEGRO_BITMAP *allegroSurface = al_create_bitmap(dimensions.x, dimensions.y);
				AE::Graphics::Surface *newSurface = new AE::Graphics::SurfaceAllegro(allegroSurface);

				return newSurface;*/
				return 0;
			}

			void ContextGL1_5::endRendering()
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

			#ifdef AE_PLATFORM_WIN32
				::SwapBuffers(mDeviceContextHandle);
			#endif
			}

			void ContextGL1_5::render()
			{
			}
		}
	}
}