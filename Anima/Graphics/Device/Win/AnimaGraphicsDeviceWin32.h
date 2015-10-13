#ifndef __AE_GRAPHICS_DEVICE_WIN32__
#define __AE_GRAPHICS_DEVICE_WIN32__

#include "AnimaGraphicsDevice.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDrawingContextDesc.h"
#include "AnimaPlatform.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class DeviceWin32 : public AE::Graphics::Device
		{
		public:
			DeviceWin32(const DISPLAY_DEVICE &displayDevice);
			virtual ~DeviceWin32();

			AE::Graphics::DeviceContext* createDeviceContext(AE::uint options);
			std::wstring& _getDeviceName() { return mDeviceName; }

		protected:
			std::wstring mDeviceName;
		};
	}
}

#endif