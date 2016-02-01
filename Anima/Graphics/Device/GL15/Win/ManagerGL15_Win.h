#ifndef __AE_GRAPHICS_DEVICE_MANAGER_GL15_WIN__
#define __AE_GRAPHICS_DEVICE_MANAGER_GL15_WIN__

#include "Anima/Graphics/Device/Manager.h"

#include "Anima/Platform.h"
#include "Anima/Graphics/Device/GL15/GLHeaders.h"
#include "Anima/Graphics/Device/Driver.h"
#include "Anima/Graphics/Device/Context.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		class SurfaceFactory;

		namespace Device
		{
			class Driver;

			class ManagerGL15 : public AE::Graphics::Device::Manager
			{
			public:
				ManagerGL15();
				virtual ~ManagerGL15();

				bool			install(AE::uint options);
				bool			uninstall();

				AE::Graphics::Device::Driver*
								acquireDeviceDriver(AE::uint graphicsDeviceNumber, AE::Graphics::Device::DriverType driverType = AE::Graphics::Device::DT_NONE);

				void			_initializeExtensions();

/*#           ifdef AE_PLATFORM_WIN32
				void			_setDeviceContext(HDC hdc) { mDeviceContext = hdc; }
#           endif*/

			protected:
				bool			_checkOpenGLExtension(char* extensionName);

/*#           ifdef AE_PLATFORM_WIN32
				HDC				mDeviceContext;
				HGLRC			mRenderingContext;
#           elif defined(AE_PLATFORM_OSX)
#               if AE_PLATFORM_OSX_MINOR_VERSION  6
					AGLContext mAGLContext;
#               else
					// ...
#               endif
#           endif*/
			};
		}
	}
}

#endif
