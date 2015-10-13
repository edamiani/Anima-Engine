#ifndef __AE_OS_WINDOW_MANAGER_WIN32__
#define __AE_OS_WINDOW_MANAGER_WIN32__

#include "AnimaOSWindowManager.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class WindowManagerWin32 : public AE::OS::WindowManager
		{
		public:
			WindowManagerWin32();
			virtual ~WindowManagerWin32();

			AE::OS::Window* createWindow(const std::string &windowTitle, const AE::Math::Point2 &dimensions);
			void destroyWindow(AE::OS::Window *window);

		private:
			std::list<AE::OS::Window *> mWindows;
		};
	}
}

#endif