#include "../include/AnimaGraphicsDeviceManagerGL21.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceDriverGL21.h"
#include "../include/AnimaGraphicsDevicePixelBufferDesc.h"
#include "../include/AnimaGraphicsDevicePixelBufferFactoryGL21.h"
#include "../include/AnimaGraphicsEnums.h"

#include <cassert>
#include <string.h>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ManagerGL21::ManagerGL21()
			{
				mInstance = this;
			}

			ManagerGL21::~ManagerGL21()
			{
				mInstance = 0;
			}

			bool ManagerGL21::install(AE::uint options)
			{
				if(mParent != 0)
				{
					mPixelBufferFactory = new AE::Graphics::Device::PixelBufferFactoryGL21();

					mIsInstalled = true;

					return true;
				}
				else
					return false;
			}

			bool ManagerGL21::uninstall()
			{
				delete mPixelBufferFactory;

				return true;
			}

			AE::Graphics::Device::Driver* ManagerGL21::acquireDeviceDriver(AE::uint graphicsDeviceNumber, AE::Graphics::Device::DriverType driverType)
			{
				// TODO implement adapter counting
				/*if(mDeviceDrivers.find(graphicsDeviceNumber) != mDeviceDrivers.end())
					throw AE::Exception(AE::ET_ALREADY_EXISTS, "AE::Graphics::ManagerAllegro::acquireDeviceDriver(): Device driver already acquired.");
				else if(graphicsDeviceNumber >= mAdapters.size())
					throw AE::Exception(AE::ET_NOT_FOUND, "AE::Graphics::ManagerAllegro::acquireDeviceDriver(): graphicsDeviceNumber exceeds the number of existing devices.");*/

				mDeviceDrivers[graphicsDeviceNumber] = new AE::Graphics::Device::DriverGL21(graphicsDeviceNumber);

				return mDeviceDrivers[graphicsDeviceNumber];
			}

			bool ManagerGL21::_checkOpenGLExtension(char* extensionName)
			{
				// get the list of supported extensions
				char* extensionList = (char*) glGetString(GL_EXTENSIONS);
				size_t error = glGetError();

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

			void ManagerGL21::_initializeExtensions()
			{
				/*if(_checkOpenGLExtension("GL_EXT_draw_range_elements"))
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

				if(_checkOpenGLExtension("GL_ARB_window_pos"))
				{
					glWindowPos2i = (PFNGLWINDOWPOS2IPROC) wglGetProcAddress("glWindowPos2iARB");
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
				}*/
			}
		}
	}
}
