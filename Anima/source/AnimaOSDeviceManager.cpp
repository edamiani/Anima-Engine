#include "../include/AnimaOSDeviceManager.h"

#include <cassert>

// Always needed, because we're using Allegro to enumerate the monitors
//#include "allegro5/allegro.h"

#ifdef AE_PLATFORM_ALLEGRO
//#	include "../include/AnimaGraphicsDeviceManagerAllegro.h"
#elif defined(AE_PLATFORM_OGRE)
//#	include "Ogre.h"
#else
#	if defined(AE_PLATFORM_WIN32)
//#		include "../include/AnimaGraphicsDeviceWin32.h"
#	else

#	endif
#endif

AE::OS::DeviceManager* AE::OS::DeviceManager::mInstance = 0;

namespace AE
{
	namespace OS
	{
		DeviceManager::DeviceManager()
		{
#		ifdef AE_PLATFORM_ALLEGRO
			/*mNumberOfGraphicsDevices = al_get_num_video_adapters();

			for(AE::uint i = 0; i < mNumberOfGraphicsDevices; i++)
				mGraphicsDevices.push_back(new AE::Graphics::DeviceAllegro(i));*/
#		else
			/*al_init();

			mNumberOfGraphicsDevices = al_get_num_video_adapters();

			for(AE::uint i = 0; i < mNumberOfGraphicsDevices; i++)
				mGraphicsDevices.push_back(new AE::Graphics::DeviceAllegro(i));

			al_uninstall_system();*/
#		endif
		}

		DeviceManager::~DeviceManager()
		{
			//mGraphicsDevices.clear();
		}

		AE::OS::Device* DeviceManager::acquireDevice(AE::OS::DeviceType deviceType, AE::uint options)
		{
			switch(deviceType)
			{
			/*case AE::OS::DT_GRAPHICS_PRIMARY:
				return _acquireGraphicsDevice(options, 0);
			case AE::OS::DT_GRAPHICS_SECONDARY:
				return _acquireGraphicsDevice(options, 1);*/
			case AE::OS::DT_INPUT_MOUSE:
				return _acquireMouse(options);
			default:
				return 0;
			}
		}

		/*AE::Graphics::Device* DeviceManager::getGraphicsDevice(AE::uint graphicsDeviceNumber)
		{
			if(graphicsDeviceNumber >= mNumberOfGraphicsDevices)
				graphicsDeviceNumber = 0;

			return mGraphicsDevices[graphicsDeviceNumber];
		}*/

		AE::OS::DeviceManager* DeviceManager::initialize()
		{
			mInstance = new AE::OS::DeviceManager();
			return mInstance;
		}

		void DeviceManager::shutdown()
		{
			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}

		/*AE::OS::Device* DeviceManager::_acquireGraphicsDevice(AE::uint options, AE::uchar deviceNumber)
		{
			AE::OS::Device *device = 0;
			bool deviceFound = false;*/

#	ifdef AE_PLATFORM_ALLEGRO

#	else
#		if defined(AE_PLATFORM_WIN32)
			/*DISPLAY_DEVICE displayDevice;
			displayDevice.cb = sizeof DISPLAY_DEVICE;

			int i = 0;
			while(::EnumDisplayDevices(NULL, i, &displayDevice, EDD_GET_DEVICE_INTERFACE_NAME) != 0)
			{
				if(displayDevice.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP && i == deviceNumber)
				{
					deviceFound = true;
					break;
				}
				i++;
			}

			if(!deviceFound) 
				return 0;

			device = new AE::Graphics::DeviceWin32(displayDevice);*/

#		else
			//Other platform
#		endif
#	endif

			/*if(options & AE::OS::GDO_HARDWARE)
			{
			#ifdef AE_PLATFORM_WIN32
				if(options & AE::OS::GDO_OPENGL)
					int x = 0;//device = new AE::Graphics::DeviceOpenGL();
				else
					// Uses DX9, both if it was defined as such or if the option was undefined
					int x = 0;//device = new AE::Graphics::DeviceDX9();
			#else
				int x = 0;//device = new AE::Graphics::DeviceOpenGL();
			#endif
			}
			else
			{
				//software
			}*/

			//assert(device);
			//return device;
		//}

		AE::OS::Device* DeviceManager::_acquireMouse(AE::uint options)
		{
			AE::OS::Device *device = 0;

			#ifdef AE_PLATFORM_WIN32

			#else
				// Other platform

			#endif

			assert(device);
			return device;
		}
	}
}