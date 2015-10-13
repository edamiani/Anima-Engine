#include "../include/AnimaGraphicsDeviceWin32_DX9.h"
#include "../include/AnimaGraphicsDeviceContextDX9.h"
#include "../include/AnimaGraphicsEnums.h"
#include "../include/AnimaOSWindowWin32.h"

namespace AE
{
	namespace Graphics
	{
		DeviceWin32_DX9::DeviceWin32_DX9(const DISPLAY_DEVICE &displayDevice)
		{
			mDeviceName = displayDevice.DeviceName;

			IDirect3D9 *mD3d9 = static_cast<AE::Graphics::ManagerDX9 *>(AE::Graphics::ManagerDX9::getInstance())->_getD3D9Object();
		}

		DeviceWin32_DX9::~DeviceWin32_DX9()
		{
			mD3d9->Release();			
		}

		AE::Graphics::DrawingContext* DeviceWin32_DX9::createDrawingContext(AE::uint options, AE::OS::Window *window)
		{
			HWND windowHandle = static_cast<AE::OS::WindowWin32 *>(window)->_getWindowHandle();

			AE::Graphics::DrawingContext *drawingContext = new AE::Graphics::DrawingContextDX9(this, static_cast<AE::OS::WindowWin32 *>(window));

			return drawingContext;
		}
	}
}