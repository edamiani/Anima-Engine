#include "../include/AnimaGraphicsDeviceContextDX11.h"
#include "../include/AnimaGraphicsDeviceDriverDX11.h"
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
			ContextDX11::ContextDX11(AE::Graphics::Device::Driver *deviceDriver, const AE::Math::Point2 &dimensions, HWND outputWindow) 
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

				IDXGIFactory1 *dxgiFactory = static_cast<AE::Graphics::Device::ManagerDX11 *>(AE::Graphics::Device::Manager::getInstance())->_getDXGIFactory();
				ID3D11Device *d3d11Device = static_cast<AE::Graphics::Device::DriverDX11 *>(deviceDriver)->_getD3d11Device();
				
				HRESULT result = dxgiFactory->CreateSwapChain(d3d11Device, &swapChainDesc, &mDXGISwapChain);
				assert(result != DXGI_ERROR_INVALID_CALL);
				assert(result != E_OUTOFMEMORY);
				assert(result == S_OK);

				ID3D11Texture2D* buffer;
				result = mDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&buffer);
				assert(result == S_OK);

				result = d3d11Device->CreateRenderTargetView(buffer, NULL, &mD3d11RenderTarget);
				assert(result == S_OK);

				buffer->Release();

				mD3d11DeviceContext = static_cast<AE::Graphics::Device::DriverDX11 *>(deviceDriver)->_getD3d11DeviceContext();
				mD3d11DeviceContext->OMSetRenderTargets(1, &mD3d11RenderTarget, NULL);
			}

			ContextDX11::~ContextDX11()
			{
				mD3d11RenderTarget->Release();
				mDXGISwapChain->Release();
			}

			/*AE::uint DeviceContextAllegro::createDrawingContext(AE::Graphics::SurfaceFormat surfaceFormat)
			{
				return 0;
			}*/

			bool ContextDX11::beginRendering()
			{
				float clearColor[4] = {1.0f, 1.0f, 1.0f, 1.0f}; // red, green, blue, alpha
				mD3d11DeviceContext->ClearRenderTargetView(mD3d11RenderTarget, clearColor);

				return true;
			}

			bool ContextDX11::beginRendering(const AE::Graphics::Color &clearColor)
			{
				float clearColorFloat[4] = {clearColor.R / 255.0f, clearColor.G / 255.0f, clearColor.B / 255.0f, clearColor.A / 255.0f}; // red, green, blue, alpha
				mD3d11DeviceContext->ClearRenderTargetView(mD3d11RenderTarget, clearColorFloat);

				return true;
			}

			AE::Graphics::Surface* ContextDX11::createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory)
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

			void ContextDX11::endRendering()
			{
				mDXGISwapChain->Present(0, 0);
			}

			void ContextDX11::render()
			{
			}
		}
	}
}