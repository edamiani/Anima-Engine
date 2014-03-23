#include "../include/AnimaGraphicsDeviceDriverDX10.h"

#include "../include/AnimaGraphicsDeviceContextDX10.h"
#include "../include/AnimaOSWindowWin.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			DriverDX10::DriverDX10(AE::uint deviceId, IDXGIAdapter1 *device) 
				: Driver(deviceId, AE::Graphics::Device::DT_DIRECT3D10) 
			{
				HRESULT result = D3D10CreateDevice(device, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_BGRA_SUPPORT, D3D10_SDK_VERSION, &mD3d10Device);
				assert(result == S_OK);
			}

			DriverDX10::~DriverDX10() 
			{
				mD3d10Device->Release();
			}

			AE::Graphics::Device::Context* DriverDX10::createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName)
			{
				HWND windowHandle = static_cast<AE::OS::WindowWin *>(contextDesc.parentWindow)->_getWindowHandle();
				AE::Graphics::Device::Context *deviceContext = new AE::Graphics::Device::ContextDX10(this, contextDesc.parentWindow->getDimensions(), windowHandle);

				if (contextDesc.parentWindow) 
					contextDesc.parentWindow->attachDeviceContext(deviceContext);

				return deviceContext;
			}
		}
	}
}