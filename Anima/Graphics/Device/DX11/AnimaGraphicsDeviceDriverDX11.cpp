#include "../include/AnimaGraphicsDeviceDriverDX11.h"

#include "../include/AnimaGraphicsDeviceContextDX11.h"
#include "../include/AnimaOSWindowWin.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			DriverDX11::DriverDX11(AE::uint deviceId, IDXGIAdapter1 *device) 
				: Driver(deviceId, AE::Graphics::Device::DT_DIRECT3D10) 
			{
				D3D_FEATURE_LEVEL featureLevels[] =
				{
					D3D_FEATURE_LEVEL_11_0,
					D3D_FEATURE_LEVEL_10_1,
					D3D_FEATURE_LEVEL_10_0,
				};

				HRESULT result = D3D11CreateDevice(device, D3D_DRIVER_TYPE_HARDWARE, NULL, D3D11_CREATE_DEVICE_BGRA_SUPPORT, featureLevels, 3,
					D3D11_SDK_VERSION, &mD3d11Device, &mFeatureLevel, &mD3d11DeviceContext);
				assert(result == S_OK);
			}

			DriverDX11::~DriverDX11() 
			{
				mD3d11DeviceContext->Release();
				mD3d11Device->Release();
			}

			AE::Graphics::Device::Context* DriverDX11::createDeviceContext(AE::OS::Window *window, const std::string &contextName)
			{
				HWND windowHandle = static_cast<AE::OS::WindowWin *>(window)->_getWindowHandle();
				AE::Graphics::Device::Context *deviceContext = new AE::Graphics::Device::ContextDX11(this, window->getDimensions(), windowHandle);

				window->attachDeviceContext(deviceContext);

				return deviceContext;
			}
		}
	}
}