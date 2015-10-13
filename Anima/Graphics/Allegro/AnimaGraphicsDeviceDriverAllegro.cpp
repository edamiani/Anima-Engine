#include "../include/AnimaGraphicsDeviceDriverAllegro.h"

#include "../include/AnimaGraphicsDeviceContextAllegro.h"
#include "../include/AnimaOSWindowAllegro.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			DriverAllegro::DriverAllegro(AE::uint deviceId, AE::Graphics::Device::DriverType driverType) 
				: Driver(deviceId, driverType) 
			{
				al_get_monitor_info(mDeviceId, &mMonitorInfo);
			}

			DriverAllegro::~DriverAllegro() 
			{
			}

			AE::Graphics::Device::Context* DriverAllegro::createDeviceContext(AE::OS::Window *window, const std::string &contextName)
			{
				AE::Math::Point2 dimensions = window->getDimensions();
				AE::Graphics::Device::Context *deviceContext = new AE::Graphics::Device::ContextAllegro(this, window);

				window->attachDeviceContext(deviceContext);

				return deviceContext;
			}
		}
	}
}