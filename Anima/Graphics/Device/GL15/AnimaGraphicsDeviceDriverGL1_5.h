#ifndef __AE_GRAPHICS_DEVICE_DRIVER_GL1_5__
#define __AE_GRAPHICS_DEVICE_DRIVER_GL1_5__

#include "AnimaGraphicsDeviceDriver.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class DriverGL1_5 : public AE::Graphics::Device::Driver
			{
			public:
				DriverGL1_5(AE::uint deviceId);
				~DriverGL1_5();

				AE::Graphics::Device::Context* createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName = "");

			protected:

			};
		}
	}
}

#endif
