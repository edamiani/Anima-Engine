#ifndef __AE_OS_WINDOW_MANAGER_OSX__
#define __AE_OS_WINDOW_MANAGER_OSX__

#include "AnimaOSWindowManager.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class WindowManagerOSX : public AE::OS::WindowManager
		{
		public:
			WindowManagerOSX();
			virtual ~WindowManagerOSX();

			AE::OS::Window* createWindow(const std::string &windowTitle, const AE::Math::Point2 &dimensions);
			void destroyWindow(AE::OS::Window *window);

		private:
			std::list<AE::OS::Window *> mWindows;
		};
	}
}

#endif