#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_DX10__
#define __AE_GRAPHICS_DEVICE_CONTEXT_DX10__

#include "AnimaGraphicsDeviceManagerDX10.h"
#include "AnimaGraphicsDeviceContext.h"
//#include "AnimaGraphicsSurfaceDX9.h"
//#include "AnimaGraphicsDrawingContextDesc.h"
//#include "AnimaGraphicsDrawingContextDX9.h"

#include "d3d10.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextDX10 : public AE::Graphics::Device::Context
			{
			public:
				ContextDX10(AE::Graphics::Device::Driver *deviceDriver, const AE::Math::Point2 &dimensions, HWND outputWindow);
				virtual ~ContextDX10();

				bool beginRendering();
				bool beginRendering(const AE::Graphics::Color &clearColor);
				//AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
				AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory = true);
				void endRendering();
				void render();

			protected:
				ID3D10Device *mD3d10Device;
				ID3D10RenderTargetView *mD3d10RenderTarget;
				IDXGISwapChain *mDXGISwapChain;
			};
		}
	}
}

#endif