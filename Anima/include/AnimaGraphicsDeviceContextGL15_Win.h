#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL15_WIN__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL15_WIN__

#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceContextDesc.h"
#include "AnimaGraphicsDeviceGLHeaders.h"
#include "AnimaOSWindow.h"
#include "AnimaPlatform.h"

#if defined(AE_PLATFORM_OSX)
//#   include "AnimaGraphicsDeviceContextCocoaImpl.h"
    class AnimaGraphicsDeviceContextCocoaImpl;
#endif

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL15 : public AE::Graphics::Device::Context
			{
			public:
				ContextGL15(AE::Graphics::Device::ContextDesc &contextDesc, AE::Graphics::Device::Driver *deviceDriver);
				virtual ~ContextGL15();

				bool beginRendering();
				bool beginRendering(const AE::Graphics::Color &clearColor);
				//AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
				//AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory);
				void endRendering();
				void render();

			protected:
				void _setDeviceContext(HDC hdc) { mDeviceContextHandle = hdc; }

				HDC mDeviceContextHandle;
				HGLRC mRenderingContext;
			};
		}
	}
}

#endif