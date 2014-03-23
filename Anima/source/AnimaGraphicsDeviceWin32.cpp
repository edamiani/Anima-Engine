#include "../include/AnimaGraphicsDeviceContextDX9.h"
#include "../include/AnimaGraphicsDeviceContextGL.h"
#include "../include/AnimaGraphicsDeviceWin32.h"
#include "../include/AnimaGraphicsEnums.h"
#include "../include/AnimaOSWindowWin32.h"

namespace AE
{
	namespace Graphics
	{
		DeviceWin32::DeviceWin32(const DISPLAY_DEVICE &displayDevice)
		{
			mDeviceName = displayDevice.DeviceName;
		}

		DeviceWin32::~DeviceWin32()
		{
			
		}

		AE::Graphics::DeviceContext* DeviceWin32::createDeviceContext(AE::uint options)
		{
			//HWND windowHandle = static_cast<AE::OS::WindowWin32 *>(window)->_getWindowHandle();

			AE::uint graphicsManagerOption = AE::Graphics::Manager::getInstance()->getOptions();

			AE::Graphics::DeviceContext *deviceContext = 0;
			if(graphicsManagerOption & AE::Graphics::GMO_HARDWARE)
			{
				if(graphicsManagerOption & AE::Graphics::GMO_OPENGL)
					deviceContext = new AE::Graphics::DeviceContextGL(this);
				else
					deviceContext = new AE::Graphics::DeviceContextDX9(this);
			}

			return deviceContext;
		}
	}
}