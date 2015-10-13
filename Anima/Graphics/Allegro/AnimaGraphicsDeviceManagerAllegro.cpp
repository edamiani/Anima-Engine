#include "../include/AnimaGraphicsDeviceManagerAllegro.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceDriverAllegro.h"
#include "../include/AnimaGraphicsEnums.h"
#include "../include/AnimaOSWindowAllegro.h"

#ifdef AE_PLATFORM_ALLEGRO_DX9
	#include "../include/AnimaGraphicsDeviceContextAllegroDX9.h"
#else
	#include "../include/AnimaGraphicsDeviceContextAllegro.h"
#endif

AE::Graphics::Device::ManagerAllegro* AE::Singleton<AE::Graphics::Device::ManagerAllegro>::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ManagerAllegro::ManagerAllegro()
			{
				mInstance = this;
			}

			ManagerAllegro::~ManagerAllegro()
			{
				mInstance = 0;
			}

			bool ManagerAllegro::install(AE::uint options)
			{
				//if(!al_is_system_installed())
					//al_init();
				//al_get_monitor_info(graphicsDeviceNumber, &mMonitorInfo);

				mIsInstalled = true;

				return true;
			}

			bool ManagerAllegro::uninstall()
			{
				mIsInstalled = false;

				return true;
			}

			AE::Graphics::Device::Driver* ManagerAllegro::acquireDeviceDriver(AE::uint graphicsDeviceNumber, AE::Graphics::Device::DriverType driverType)
			{
				if(mDeviceDrivers.find(graphicsDeviceNumber) != mDeviceDrivers.end())
					throw AE::Exception(AE::ET_ALREADY_EXISTS, "AE::Graphics::ManagerAllegro::acquireDeviceDriver(): Device driver already acquired.");

				mDeviceDrivers[graphicsDeviceNumber] = new AE::Graphics::Device::DriverAllegro(graphicsDeviceNumber, driverType);

				return mDeviceDrivers[graphicsDeviceNumber];
			}

			/*AE::Graphics::Device::Context* ManagerAllegro::createDeviceContext(AE::uint graphicsDeviceNumber, const AE::Math::Point2 &dimensions, AE::Graphics::Device::ContextOption deviceContextOption, const std::string &contextName)
			{
				AE::Graphics::Device::Context *deviceContext = 0;

	#		ifdef AE_PLATFORM_ALLEGRO_DX9
				al_set_new_display_flags(ALLEGRO_DIRECT3D);
				deviceContext = new AE::Graphics::Device::ContextAllegroDX9(this, dimensions, deviceContextOptions);
	#		else
				deviceContext = new AE::Graphics::Device::ContextAllegro(this, dimensions, deviceContextOption);
	#		endif

				return deviceContext;
			}

			bool ManagerAllegro::install(AE::uint options)
			{
				return true;
			}*/
		}
	}
}