#ifndef __AE_OS_WINDOW_MANAGER_ALLEGRO__
#define __AE_OS_WINDOW_MANAGER_ALLEGRO__

#include "AnimaOSWindowManager.h"

#include "AnimaGraphicsEnums.h"
#include "AnimaSingleton.h"

#include "allegro5/allegro.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class WindowManagerAllegro : public AE::OS::WindowManager
		{
		public:
			WindowManagerAllegro();
			virtual ~WindowManagerAllegro();

			bool install(AE::uint options);
			bool uninstall();

			AE::OS::Window* createWindow(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Driver *deviceDriver);
			void destroyWindow(AE::OS::Window *window);

			AE::OS::Window* _getWindow(ALLEGRO_DISPLAY* allegroDisplay);

		private:
			
		};
	}
}

#endif