#ifndef __AE_GRAPHICS_DEVICE_OGRE__
#define __AE_GRAPHICS_DEVICE_OGRE__

#include "AnimaGraphicsDevice.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDrawingContextDesc.h"
#include "AnimaPlatform.h"

#include "Ogre.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class DeviceOgre : public AE::Graphics::Device
		{
		public:
			DeviceOgre(AE::uint graphicsDeviceNumber);
			virtual ~DeviceOgre();

			AE::Graphics::Device::Driver* acquireDriver(AE::Graphics::DriverType driverType);
			AE::Graphics::DeviceContext* createDeviceContext(const AE::Math::Point2 &dimensions, AE::Graphics::DeviceContextOption deviceContextOptions, const std::string &contextName = "");
			bool initialize(AE::uint options);

		protected:
			Ogre::Root*		mOgreRoot;
			//ALLEGRO_MONITOR_INFO mMonitorInfo;
			bool			mHasInitialized;
		};
	}
}

#endif