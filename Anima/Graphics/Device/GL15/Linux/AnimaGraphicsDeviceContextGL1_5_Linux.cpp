#include "../include/AnimaGraphicsDeviceContextGL1_5.h"
#include "../include/AnimaGraphicsDeviceDriverGL1_5.h"
#include "../include/AnimaGraphicsDeviceManagerGL1_5.h"
#include "../include/AnimaGraphicsSurfaceDesc.h"
#include "../include/AnimaGraphicsSurfaceFactory.h"
#include "../include/AnimaPlatform.h"

#include "../include/AnimaMathMatrix4.h"
#include "../include/AnimaGraphicsViewport.h"
#include "../include/AnimaGraphicsCamera.h"

#include "../include/AnimaOSWindowLinux.h"
#include "../include/AnimaOSWindowManagerLinux.h"

#include <cassert>
#include <string>

#include <stdio.h>


namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ContextGL1_5::ContextGL1_5(AE::Graphics::Device::ContextDesc &contextDesc, AE::Graphics::Device::Driver *deviceDriver)
				: Context(deviceDriver)
			{
//				mDeviceContextHandle = ::GetDC(static_cast<AE::OS::WindowWin *>(contextDesc.parentWindow)->_getWindowHandle());

				AE::int8 redBits = 0, redShift = 0, greenBits = 0, greenShift = 0, blueBits = 0, blueShift = 0, alphaBits = 0, alphaShift = 0;
				AE::Graphics::SurfaceFormat surfaceFormat = contextDesc.getSurfaceFormat();
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
					case SF_R8G8B8A8:
						redBits = 8; redShift = 16;
						greenBits = 8; greenShift = 8;
						blueBits = 8; blueShift = 0;
						alphaBits = 8; alphaShift = 24;
						break;
					case SF_R8G8B8X8:
						redBits = 8; redShift = 16;
						greenBits = 8; greenShift = 8;
						blueBits = 8; blueShift = 0;
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
                    default:
                        break;
				}

				// Linux context here

				// Configurar o formato do pixel
				::Window window = static_cast<AE::OS::WindowLinux *>(contextDesc.parentWindow)->_getX11Window();
				::Display *display = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance())->_getX11Display();
				XVisualInfo *visualInfo;

				GLint attributes[] = { GLX_RGBA, GLX_DEPTH_SIZE, contextDesc.getColorDepth(), GLX_DOUBLEBUFFER, None };


                if((visualInfo = glXChooseVisual(display, 0, attributes)) == NULL)
                {
                    if(contextDesc.getColorDepth() == 32)
                    {
                        attributes[2] = 24;

                        if((visualInfo = glXChooseVisual(display, 0, attributes)) == NULL)
                        {
                            printf("\n\tno matching visual\n\n");
                            exit(0);
                        }
                    }
                }

                /*Window rootWindow = DefaultRootWindow(display);
                Colormap colorMap;
                if((colorMap = XCreateColormap(display, rootWindow, visualInfo->visual, AllocNone)) == 0)
                {
                    printf("\n\tcannot create colormap\n\n");
                    exit(0);
                }*/

				// Criar o Contexto
				if((mGLXContext = glXCreateContext(display, visualInfo, NULL, GL_TRUE)) == NULL)
				{
					// TODO work this error message - Nivaldo
                    printf("\n\tcannot create gl context\n\n");
                    exit(0);
                }

                glXMakeCurrent(display, window, mGLXContext);

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
				::Display *x11display = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance())->AE::OS::WindowManagerLinux::_getX11Display();

// TODO should I do something else about these comments or can I delete them? - Nivaldo
				// Resets the screen mode
				//ChangeDisplaySettings(0, 0);

				// Make the rendering context not current
				::glXMakeCurrent(x11display, None, NULL);

				// Delete the rendering context
				::glXDestroyContext(x11display, mGLXContext); // TODO should I be doing this? - Nivaldo

				// Delete the window's device context
//				::DeleteDC(mDeviceContextHandle);

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



				GLuint *pImage = (GLuint *)(malloc(sizeof(GLuint)));
				pImage[0] = 0xFFFFFFFF;
				glRasterPos2i(50, 50);
				glDrawPixels(1, 1, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, pImage);
				free(pImage);

				return true;
			}

			bool ContextGL1_5::beginRendering(const AE::Graphics::Color &clearColor)
			{
				//AE::Graphics::Color backgroundColor = mViewport->getBackgroundColor();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glClearColor(clearColor.R / 255.0f, clearColor.G / 255.0f, clearColor.B / 255.0f, 1.0f);
				glClearDepth(1.0f);

				glShadeModel(GL_SMOOTH);

//				AE::Math::Matrix4 viewMatrix = mViewport->getCamera()->getViewMatrix();
//				AE::Math::Matrix4 projectionMatrix = mViewport->getProjectionMatrix();

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				//viewMatrix = parentTransformation * viewMatrix;
				//viewMatrix = viewMatrix.transpose();
			#if AE_DOUBLE_PRECISION
//				glMultMatrixd(viewMatrix._m);
			#else
//				glMultMatrixf(viewMatrix._m);
			#endif
				GLdouble viewMatrixGL[16];
				glGetDoublev(GL_MODELVIEW_MATRIX, viewMatrixGL);

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
//				projectionMatrix = projectionMatrix.transpose();
			#if AE_DOUBLE_PRECISION
//				glMultMatrixd(projectionMatrix._m);
			#else
//				glMultMatrixf(projectionMatrix._m);
			#endif

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
				glViewport(0, 0, mFrameBuffer->getDimensions().x, mFrameBuffer->getDimensions().y);

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
				free(pImage);

                ::Display *display = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance())->_getX11Display();
                ::Window window = static_cast<AE::OS::WindowLinux *>(mParentWindow)->_getX11Window();
                glXSwapBuffers( display, window );
			}

			void ContextGL1_5::render()
			{
			}
		}
	}
}
