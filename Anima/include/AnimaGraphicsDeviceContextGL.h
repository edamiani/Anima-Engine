#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL__

#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDevice.h"
#include "AnimaGraphicsSurfaceGL.h"
#include "AnimaGraphicsDrawingContextDesc.h"
#include "AnimaGraphicsDrawingContextGL.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		class DeviceContextGL : public AE::Graphics::DeviceContext
		{
		public:
			DeviceContextGL(AE::Graphics::Device *graphicsDevice);
			virtual ~DeviceContextGL();

			bool beginRendering();
			AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
			AE::Graphics::Surface* createOffscreenSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat);
			void endRendering();

		protected:
		#ifdef WIN32
			void _setDeviceContext(HDC hdc) { mDeviceContext = hdc; }
		#endif

			AE::Graphics::Device *mGraphicsDevice;

		#ifdef AE_PLATFORM_WIN32
			HDC mDeviceContext;
			HGLRC mRenderingContext;
		#elif defined(MAC_OS_X_VERSION_10_0)
			AGLContext mAGLContext;
		#endif
		};
	}
}

#endif