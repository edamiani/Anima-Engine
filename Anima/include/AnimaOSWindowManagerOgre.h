#ifndef __AE_OS_WINDOW_MANAGER_OGRE__
#define __AE_OS_WINDOW_MANAGER_OGRE__

#include "AnimaOSWindowManager.h"
#include "AnimaGraphicsEnums.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class WindowManagerOgre : public AE::OS::WindowManager
		{
		public:
			WindowManagerOgre();
			virtual ~WindowManagerOgre();

			AE::OS::Window* createWindow(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, AE::Graphics::DeviceContextOption deviceContextOptions = AE::Graphics::DCO_NO_OPTIONS, AE::uint numVideoAdapter = 0);
			void destroyWindow(AE::OS::Window *window);

			//AE::OS::Window* _getWindow(ALLEGRO_DISPLAY* allegroDisplay);

		private:
			std::list<AE::OS::Window *> mWindows;
		};
	}
}

#endif