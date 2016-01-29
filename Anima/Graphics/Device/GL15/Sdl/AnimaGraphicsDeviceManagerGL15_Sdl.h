#ifndef __AE_GRAPHICS_DEVICE_MANAGER_GL15_SDL__
#define __AE_GRAPHICS_DEVICE_MANAGER_GL15_SDL__

#include "Anima/Graphics/Device/AnimaGraphicsDeviceManager.h"

#include "Anima/AnimaPlatform.h"
#include "../AnimaGraphicsDeviceGLHeaders.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceDriver.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"

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

			protected:
				bool			_checkOpenGLExtension(char* extensionName);
			};
		}
	}
}

#endif
