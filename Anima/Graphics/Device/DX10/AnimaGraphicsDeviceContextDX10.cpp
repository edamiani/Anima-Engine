#include "../include/AnimaGraphicsDeviceContextDX10.h"
#include "../include/AnimaGraphicsDeviceDriverDX10.h"
//#include "../include/AnimaGraphicsSurfaceAllegro.h"
#include "../include/AnimaPlatform.h"

#include <cassert>
#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ContextDX10::ContextDX10(AE::Graphics::Device::Driver *deviceDriver, const AE::Math::Point2 &dimensions, HWND outputWindow) 
				: Context(deviceDriver)
			{
				DXGI_SWAP_CHAIN_DESC swapChainDesc;
				ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
				swapChainDesc.BufferCount = 1;
				swapChainDesc.BufferDesc.Width = dimensions.x;
				swapChainDesc.BufferDesc.Height = dimensions.y;
				swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
				swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
				swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
				swapChainDesc.OutputWindow = outputWindow;
				swapChainDesc.SampleDesc.Count = 1;
				swapChainDesc.SampleDesc.Quality = 0;
				swapChainDesc.Windowed = TRUE;

				IDXGIFactory1 *dxgiFactory = static_cast<AE::Graphics::Device::ManagerDX10 *>(AE::Graphics::Device::Manager::getInstance())->_getDXGIFactory();
				mD3d10Device = static_cast<AE::Graphics::Device::DriverDX10 *>(deviceDriver)->_getD3d10Device();
				
				HRESULT result = dxgiFactory->CreateSwapChain(mD3d10Device, &swapChainDesc, &mDXGISwapChain);
				assert(result != DXGI_ERROR_INVALID_CALL);
				assert(result != E_OUTOFMEMORY);
				assert(result == S_OK);

				ID3D10Texture2D* buffer;
				result = mDXGISwapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&buffer);
				assert(result == S_OK);

				result = mD3d10Device->CreateRenderTargetView(buffer, NULL, &mD3d10RenderTarget);
				assert(result == S_OK);

				buffer->Release();

				mD3d10Device->OMSetRenderTargets(1, &mD3d10RenderTarget, NULL);
			}

			ContextDX10::~ContextDX10()
			{
				mD3d10RenderTarget->Release();
				mDXGISwapChain->Release();
			}

			/*AE::uint DeviceContextAllegro::createDrawingContext(AE::Graphics::SurfaceFormat surfaceFormat)
			{
				return 0;
			}*/

			bool ContextDX10::beginRendering()
			{
				float clearColor[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // red, green, blue, alpha
				mD3d10Device->ClearRenderTargetView(mD3d10RenderTarget, clearColor);

				return true;
			}

			bool ContextDX10::beginRendering(const AE::Graphics::Color &clearColor)
			{
				float clearColorFloat[4] = {clearColor.R / 255.0f, clearColor.G / 255.0f, clearColor.B / 255.0f, clearColor.A / 255.0f}; // red, green, blue, alpha
				mD3d10Device->ClearRenderTargetView(mD3d10RenderTarget, clearColorFloat);

				return true;
			}

			AE::Graphics::Surface* ContextDX10::createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory)
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

			void ContextDX10::endRendering()
			{
				mDXGISwapChain->Present(0, 0);
			}

			void ContextDX10::render()
			{
			}
		}
	}
}