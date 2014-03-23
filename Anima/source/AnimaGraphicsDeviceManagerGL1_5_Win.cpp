#include "../include/AnimaGraphicsDeviceManagerGL1_5.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceDriverGL1_5.h"
#include "../include/AnimaGraphicsDevicePixelBufferDesc.h"
#include "../include/AnimaGraphicsDevicePixelBufferFactoryGL15.h"
#include "../include/AnimaGraphicsEnums.h"

#include <cassert>
#include <string.h>

/*#ifndef AE_PLATFORM_LINUX
// GL_EXT_draw_range_eelments (1.2)
PFNGLDRAWRANGEELEMENTSPROC		glDrawRangeElements;
#endif

// GL_EXT_multi_draw_arrays (1.4)
PFNGLMULTIDRAWARRAYSPROC		glMultiDrawArrays;
PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements;

#ifndef AE_PLATFORM_LINUX
// GL_ARB_multitexture (1.4)
PFNGLCLIENTACTIVETEXTUREPROC	glClientActiveTexture;
#endif

// GL_ARB_window_pos (1.4)
PFNGLWINDOWPOS2IPROC			glWindowPos2i;

// GL_ARB_vertex_buffer_object (1.5)
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
PFNGLUNMAPBUFFERPROC			glUnmapBuffer;*/

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ManagerGL1_5::ManagerGL1_5()
			{
				mInstance = this;
			}

			ManagerGL1_5::~ManagerGL1_5()
			{
				mInstance = 0;
			}

			bool ManagerGL1_5::install(AE::uint options)
			{
				if(mParent != 0)
				{
					mPixelBufferFactory = new AE::Graphics::Device::PixelBufferFactoryGL15();

					mIsInstalled = true;

					return true;
				}
				else
					return false;
			}

			bool ManagerGL1_5::uninstall()
			{
				delete mPixelBufferFactory;

				return true;
			}

			AE::Graphics::Device::Driver* ManagerGL1_5::acquireDeviceDriver(AE::uint graphicsDeviceNumber, AE::Graphics::Device::DriverType driverType)
			{
				// TODO implement adapter counting
				/*if(mDeviceDrivers.find(graphicsDeviceNumber) != mDeviceDrivers.end())
					throw AE::Exception(AE::ET_ALREADY_EXISTS, "AE::Graphics::ManagerAllegro::acquireDeviceDriver(): Device driver already acquired.");
				else if(graphicsDeviceNumber >= mAdapters.size())
					throw AE::Exception(AE::ET_NOT_FOUND, "AE::Graphics::ManagerAllegro::acquireDeviceDriver(): graphicsDeviceNumber exceeds the number of existing devices.");*/

				mDeviceDrivers[graphicsDeviceNumber] = new AE::Graphics::Device::DriverGL1_5(graphicsDeviceNumber);

				return mDeviceDrivers[graphicsDeviceNumber];
			}

			bool ManagerGL1_5::_checkOpenGLExtension(char* extensionName)
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

			void ManagerGL1_5::_initializeExtensions()
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
