#ifndef __AE_GRAPHICS_DEVICE_DRIVER_GL21__
#define __AE_GRAPHICS_DEVICE_DRIVER_GL21__

#include "AnimaGraphicsDeviceDriver.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class DriverGL21 : public AE::Graphics::Device::Driver
			{
			public:
				DriverGL21(AE::uint deviceId);
				~DriverGL21();

				AE::Graphics::Device::Context* createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName = "");

			protected:

			};
		}
	}
}

#endif
