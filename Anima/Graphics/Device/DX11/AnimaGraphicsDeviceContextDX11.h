#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_DX11__
#define __AE_GRAPHICS_DEVICE_CONTEXT_DX11__

#include "AnimaGraphicsDeviceManagerDX11.h"
#include "AnimaGraphicsDeviceContext.h"

#include "d3d11.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextDX11 : public AE::Graphics::Device::Context
			{
			public:
				ContextDX11(AE::Graphics::Device::Driver *deviceDriver, const AE::Math::Point2 &dimensions, HWND outputWindow);
				virtual ~ContextDX11();

				bool beginRendering();
				bool beginRendering(const AE::Graphics::Color &clearColor);
				//AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
				AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory = true);
				void endRendering();
				void render();

			protected:
				ID3D11DeviceContext *mD3d11DeviceContext;
				ID3D11RenderTargetView *mD3d11RenderTarget;
				IDXGISwapChain *mDXGISwapChain;
			};
		}
	}
}

#endif