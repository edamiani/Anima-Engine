#include "../include/AnimaGraphicsDeviceContextDX9.h"
#include "../include/AnimaGraphicsManagerDX9.h"
#include "../include/AnimaGraphicsViewport.h"
#include "../include/AnimaOSWindowWin32.h"

#include <d3d9.h>

#include <string>

namespace AE
{
	namespace Graphics
	{
		DeviceContextDX9::DeviceContextDX9(AE::Graphics::DeviceWin32 *graphicsDevice) 
			: mGraphicsDevice(graphicsDevice), mD3dDevice(0)
		{
		}

		DeviceContextDX9::~DeviceContextDX9()
		{
			mD3dDevice->Release();
			mD3dDevice = NULL;
		}

		AE::uint DeviceContextDX9::createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat)
		{
			//mHDC = ::CreateDC(graphicsDevice->_getDeviceName().c_str(), NULL, NULL, NULL);
			/*int pixelFormat = ::GetPixelFormat(mHDC);
			DWORD error = ::GetLastError();
			PIXELFORMATDESCRIPTOR pfd;
			int x = ::DescribePixelFormat(mHDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
			error = ::GetLastError();*/

			mWindows.push_back(window);

			D3DPRESENT_PARAMETERS d3dpp;
			::ZeroMemory(&d3dpp, sizeof(d3dpp));

			switch(surfaceFormat)
			{
			case AE::Graphics::SF_A8R8G8B8:
				d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
				break;
			case AE::Graphics::SF_X8R8G8B8:
				d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
				break;
			case AE::Graphics::SF_A1R5G5B5:
				d3dpp.BackBufferFormat = D3DFMT_A1R5G5B5;
				break;
			case AE::Graphics::SF_X1R5G5B5:
				d3dpp.BackBufferFormat = D3DFMT_X1R5G5B5;
				break;
			case AE::Graphics::SF_R5G6B5:
				d3dpp.BackBufferFormat = D3DFMT_R5G6B5;
				break;
			default:
				d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
				break;
			}

			d3dpp.BackBufferCount = 1;
			d3dpp.BackBufferHeight = window->getWindowMetrics().height;
			d3dpp.BackBufferWidth = window->getWindowMetrics().width;
			d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
			d3dpp.hDeviceWindow = static_cast<AE::OS::WindowWin32 *>(window)->_getWindowHandle();
			d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
			d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
			d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			d3dpp.Windowed = TRUE;

			IDirect3D9 *d3d9 = static_cast<AE::Graphics::ManagerDX9 *>(AE::Graphics::ManagerDX9::getInstance())->_getD3D9Object();

			D3DADAPTER_IDENTIFIER9 adapterId;
			for(AE::uint i = 0; i < d3d9->GetAdapterCount(); i++)
			{
				d3d9->GetAdapterIdentifier(i, 0, &adapterId);
				std::string deviceName = adapterId.DeviceName;
				std::wstring deviceNameW(deviceName.begin(), deviceName.end());
				if(deviceNameW == mGraphicsDevice->_getDeviceName())
				{
					D3DCAPS9 d3dCaps;
					d3d9->GetDeviceCaps(i, D3DDEVTYPE_HAL, &d3dCaps);

					DWORD dwBehaviorFlags = 0;
					if( d3dCaps.VertexProcessingCaps != 0 )
						dwBehaviorFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
					else
						dwBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

					IDirect3DSurface9 *surfaceDX9;
					HRESULT hResult;

					if(mDrawingContexts.size() == 0)
					{
						hResult = d3d9->CreateDevice(i, D3DDEVTYPE_HAL, static_cast<AE::OS::WindowWin32 *>(window)->_getWindowHandle(),
													 dwBehaviorFlags, &d3dpp, &mD3dDevice);
						hResult = mD3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &surfaceDX9);
						assert(hResult == D3D_OK);
					}
					else
					{
						IDirect3DSwapChain9 *swapChain;
						hResult = mD3dDevice->CreateAdditionalSwapChain(&d3dpp, &swapChain);
						assert(hResult == D3D_OK);

						hResult = swapChain->GetBackBuffer(0, D3DBACKBUFFER_TYPE_MONO, &surfaceDX9);
						assert(hResult == D3D_OK);
					}

					AE::Graphics::DrawingContextDX9 *drawingContextDX9 = new AE::Graphics::DrawingContextDX9(this, surfaceDX9);
					mDrawingContexts.push_back(drawingContextDX9);
					window->setDrawingContext(drawingContextDX9);

					return (mDrawingContexts.size() - 1);
				}
			}

			// Failed
			return 0;
		}

		AE::Graphics::Surface* DeviceContextDX9::createOffscreenSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat)
		{
			D3DFORMAT format;
				
			// NB: DirectX uses the format ARGB
			switch(surfaceFormat)
			{
			case SF_A8R8G8B8:
				format = D3DFMT_A8R8G8B8;
				break;
			case SF_X8R8G8B8:
				format = D3DFMT_X8R8G8B8;
				break;
			case SF_A1R5G5B5:
				format = D3DFMT_A1R5G5B5;
				break;
			case SF_X1R5G5B5:
				format = D3DFMT_X1R5G5B5;
				break;
			case SF_R5G6B5:
				format = D3DFMT_R5G6B5;
				break;
			}

			IDirect3DSurface9 *surfaceDX9;
			D3DPOOL poolType = D3DPOOL_DEFAULT;
			mD3dDevice->CreateOffscreenPlainSurface(width, height, format, poolType, &surfaceDX9, NULL);

			AE::Graphics::Surface *surface = new AE::Graphics::SurfaceDX9(surfaceDX9);
			return surface;
		}

		bool DeviceContextDX9::beginRendering()
		{
			//mD3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

			AE::Graphics::Color backgroundColor = AE::Graphics::Manager::getInstance()->getViewport()->getBackgroundColor();
			mD3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(backgroundColor.R, backgroundColor.G, backgroundColor.B), 1.0f, 0);

			// Begin the scene
			if(SUCCEEDED(mD3dDevice->BeginScene()))
				return true;
			else
				return false;
		}

		void DeviceContextDX9::endRendering()
		{
			// End the scene
			mD3dDevice->EndScene();

			for(AE::uint i = 0; i < mWindows.size(); i++)
				mWindows[i]->render();

			mD3dDevice->Present(NULL, NULL, NULL, NULL);
		}
	}
}