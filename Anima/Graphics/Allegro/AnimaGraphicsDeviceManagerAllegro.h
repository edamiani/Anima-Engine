#ifndef __AE_GRAPHICS_DEVICE_MANAGER_ALLEGRO__
#define __AE_GRAPHICS_DEVICE_MANAGER_ALLEGRO__

#include "AnimaGraphicsDeviceManager.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceContext.h"
//#include "AnimaGraphicsDrawingContextDesc.h"
#include "AnimaPlatform.h"

#include "allegro5/allegro.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Driver;

			class ManagerAllegro : public AE::Graphics::Device::Manager
			{
			public:
				ManagerAllegro();
				virtual ~ManagerAllegro();

				bool install(AE::uint options);
				bool uninstall();

				AE::Graphics::Device::Driver* acquireDeviceDriver(AE::uint graphicsDeviceNumber, AE::Graphics::Device::DriverType driverType);
				//AE::Graphics::Device::Context* createDeviceContext(AE::Graphics::Device::Driver *devicedriver, const AE::Math::Point2 &dimensions, AE::Graphics::Device::ContextOption deviceContextOptions, const std::string &contextName = "");

			protected:
			};
		}
	}
}

#endif