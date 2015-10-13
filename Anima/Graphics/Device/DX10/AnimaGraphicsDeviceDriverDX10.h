#ifndef __AE_GRAPHICS_DEVICE_DRIVER_DX10__
#define __AE_GRAPHICS_DEVICE_DRIVER_DX10__

#include "AnimaGraphicsDeviceDriver.h"

#include "d3d10.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class DriverDX10 : public AE::Graphics::Device::Driver
			{
			public:
				DriverDX10(AE::uint deviceId, IDXGIAdapter1 *device);
				~DriverDX10();

				AE::Graphics::Device::Context* createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName = "");

				ID3D10Device* _getD3d10Device() { return mD3d10Device; }

			protected:
				ID3D10Device* mD3d10Device;
			};
		}
	}
}

#endif