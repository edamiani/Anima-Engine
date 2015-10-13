#ifndef __AE_OS_WINDOW_ALLEGRO__
#define __AE_OS_WINDOW_ALLEGRO__

#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSWindow.h"
#include "AnimaOSWindowDesc.h"

#include "allegro5/allegro.h"

namespace AE
{
	namespace Graphics
	{
		class DeviceContext;
	}

	namespace OS
	{
		class WindowAllegro : public Window
		{
		public:
			WindowAllegro(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc);
			~WindowAllegro();

			void	attachDeviceContext(AE::Graphics::Device::Context *deviceContext);
			void	close() { }
			size_t	getWindowHandle();
			void	show() { }

		protected:
		};
	}
}

#endif