#include "../include/AnimaGraphicsDeviceOgre.h"

#include "../include/AnimaGraphicsDeviceContextOgre.h"
#include "../include/AnimaGraphicsEnums.h"
#include "../include/AnimaOSWindowOgre.h"

namespace AE
{
	namespace Graphics
	{
		DeviceOgre::DeviceOgre(AE::uint graphicsDeviceNumber)
			: mHasInitialized(false)
		{
			//al_get_monitor_info(graphicsDeviceNumber, &mMonitorInfo);
			//Ogre::Root::getSingleton().createRenderWindow(
		}

		DeviceOgre::~DeviceOgre()
		{
		}

		AE::Graphics::Device::Driver* DeviceOgre::acquireDriver(AE::Graphics::DriverType driverType)
		{
			return 0;
		}

		AE::Graphics::DeviceContext* DeviceOgre::createDeviceContext(const AE::Math::Point2 &dimensions, AE::Graphics::DeviceContextOption deviceContextOptions, const std::string &contextName)
		{
			AE::Graphics::DeviceContext *deviceContext = 0;

/*#		ifdef AE_PLATFORM_ALLEGRO_DX9
			al_set_new_display_flags(ALLEGRO_DIRECT3D);
			deviceContext = new AE::Graphics::DeviceContextAllegroDX9(this, dimensions, deviceContextOptions);
#		else
			deviceContext = new AE::Graphics::DeviceContextAllegro(this, dimensions, deviceContextOptions);
#		endif*/

			return deviceContext;
		}

		bool DeviceOgre::initialize(AE::uint options)
		{
			return true;
		}
	}
}