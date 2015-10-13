#ifndef __AE_GRAPHICS_DEVICE_MANAGER_DX11__
#define __AE_GRAPHICS_DEVICE_MANAGER_DX11__

#include "AnimaGraphicsDeviceManager.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceContext.h"
//#include "AnimaGraphicsDrawingContextDesc.h"
#include "AnimaPlatform.h"

#include "dxgi.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Driver;

			class ManagerDX11 : public AE::Graphics::Device::Manager
			{
			public:
				ManagerDX11();
				virtual ~ManagerDX11();

				bool install(AE::uint options);
				bool uninstall();

				AE::Graphics::Device::Driver* acquireDeviceDriver(AE::uint graphicsDeviceNumber, AE::Graphics::Device::DriverType driverType = AE::Graphics::Device::DT_NONE);
				//AE::Graphics::Device::Context* createDeviceContext(AE::Graphics::Device::Driver *devicedriver, const AE::Math::Point2 &dimensions, AE::Graphics::Device::ContextOption deviceContextOptions, const std::string &contextName = "");

				IDXGIFactory1* _getDXGIFactory() { return mDXGIFactory; }

			protected:
				IDXGIFactory1 *mDXGIFactory;
				std::vector<IDXGIAdapter1 *> mAdapters;
			};
		}
	}
}

#endif