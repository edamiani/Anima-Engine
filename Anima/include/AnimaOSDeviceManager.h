#ifndef __AE_OS_DEVICE_MANAGER__
#define __AE_OS_DEVICE_MANAGER__

#include "AnimaOSEnums.h"
#include "AnimaPlatform.h"
#include "AnimaTypes.h"

#include <vector>

namespace AE
{
	namespace OS
	{
		class Device;

		class DeviceManager
		{
		public:
			DeviceManager();
			virtual ~DeviceManager();

			static AE::OS::DeviceManager*	getInstance() { assert(mInstance != 0); return mInstance; }
			static AE::OS::DeviceManager*	initialize();
			static void						shutdown();

			AE::OS::Device*					acquireDevice(AE::OS::DeviceType deviceType, AE::uint options);
			//AE::Graphics::Device::Driver* getGraphicsDevice(AE::uint graphicsDeviceNumber);
			//AE::uint						getNumberOfGraphicsDevices() { return mNumberOfGraphicsDevices; }

		protected:
			//AE::OS::Device*	_acquireGraphicsDevice(AE::uint options, AE::uchar deviceNumber);
			AE::OS::Device*	_acquireMouse(AE::uint options);

			//std::vector<AE::Graphics::Device *>	mGraphicsDevices;
			static AE::OS::DeviceManager		*mInstance;
			//AE::uint8							mNumberOfGraphicsDevices;
		};
	}
}

#endif
