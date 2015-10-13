#ifndef __AE_GRAPHICS_DEVICE_DRIVER_ALLEGRO__
#define __AE_GRAPHICS_DEVICE_DRIVER_ALLEGRO__

#include "AnimaGraphicsDeviceDriver.h"

#include "allegro5/allegro.h"

namespace AE
{
	namespace OS
	{
		class Window;
	}

	namespace Graphics
	{
		namespace Device
		{
			class DriverAllegro : public AE::Graphics::Device::Driver
			{
			public:
				DriverAllegro(AE::uint deviceId, AE::Graphics::Device::DriverType);
				~DriverAllegro();

				AE::Graphics::Device::Context* createDeviceContext(AE::OS::Window *window, const std::string &contextName = "");

			protected:
				ALLEGRO_MONITOR_INFO mMonitorInfo;
			};
		}
	}
}

#endif