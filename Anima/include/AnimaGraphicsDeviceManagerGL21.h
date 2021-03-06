#ifndef __AE_GRAPHICS_DEVICE_MANAGER_GL21__
#define __AE_GRAPHICS_DEVICE_MANAGER_GL21__

#include "AnimaGraphicsDeviceManager.h"

#include "AnimaGraphicsDeviceGLHeaders.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaPlatform.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		class SurfaceFactory;

		namespace Device
		{
			class Driver;

			class ManagerGL21 : public AE::Graphics::Device::Manager
			{
			public:
				ManagerGL21();
				virtual ~ManagerGL21();

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
