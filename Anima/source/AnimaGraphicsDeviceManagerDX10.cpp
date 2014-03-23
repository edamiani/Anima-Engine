#include "../include/AnimaGraphicsDeviceManagerDX10.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceDriverDX10.h"
//#include "../include/AnimaGraphicsDeviceContextAllegro.h"
#include "../include/AnimaGraphicsEnums.h"
//#include "../include/AnimaOSWindowAllegro.h"

#include <cassert>

AE::Graphics::Device::ManagerDX10* AE::Singleton<AE::Graphics::Device::ManagerDX10>::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			ManagerDX10::ManagerDX10()
			{
				mInstance = this;
			}

			ManagerDX10::~ManagerDX10()
			{
				mInstance = 0;
			}

			bool ManagerDX10::install(AE::uint options)
			{
				//if(!al_is_system_installed())
					//al_init();
				//al_get_monitor_info(graphicsDeviceNumber, &mMonitorInfo);
				HRESULT result = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)(&mDXGIFactory) );

				assert(result == S_OK);

				AE::uint i = 0;
				IDXGIAdapter1 *adapter;
				while(mDXGIFactory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND) 
				{ 
					mAdapters.push_back(adapter); 
					++i; 
				} 

				mIsInstalled = true;

				return true;
			}

			bool ManagerDX10::uninstall()
			{
				std::vector<IDXGIAdapter1 *>::iterator i;
				for(i = mAdapters.begin(); i != mAdapters.end(); i++)
					(*i)->Release();

				mAdapters.clear();

				mDXGIFactory->Release();

				mIsInstalled = false;

				return true;
			}

			AE::Graphics::Device::Driver* ManagerDX10::acquireDeviceDriver(AE::uint graphicsDeviceNumber, AE::Graphics::Device::DriverType driverType)
			{
				if(mDeviceDrivers.find(graphicsDeviceNumber) != mDeviceDrivers.end())
					throw AE::Exception(AE::ET_ALREADY_EXISTS, "AE::Graphics::ManagerAllegro::acquireDeviceDriver(): Device driver already acquired.");
				else if(graphicsDeviceNumber >= mAdapters.size())
					throw AE::Exception(AE::ET_NOT_FOUND, "AE::Graphics::ManagerAllegro::acquireDeviceDriver(): graphicsDeviceNumber exceeds the number of existing devices.");

				mDeviceDrivers[graphicsDeviceNumber] = new AE::Graphics::Device::DriverDX10(graphicsDeviceNumber, mAdapters[graphicsDeviceNumber]);

				return mDeviceDrivers[graphicsDeviceNumber];
			}
		}
	}
}