#ifndef __AE_OS_WINDOW_MANAGER_LINUX__
#define __AE_OS_WINDOW_MANAGER_LINUX__

#include "AnimaOSWindowManager.h"
#include "AnimaPlatform.h"

#include <X11/Xlib.h>

#include <list>

namespace AE
{
	namespace OS
	{
		class WindowManagerLinux: public AE::OS::WindowManager
		{
		public:

			WindowManagerLinux();
			virtual ~WindowManagerLinux();

			bool install(AE::uint options);
			bool uninstall();

			AE::OS::Window*	createWindow(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Driver *deviceDriver);
			void			destroyWindow(AE::OS::Window *window);

            AE::OS::Window*	_getAEWindow(::Window window);
			::Display*		_getX11Display() { return mX11Display; }

		private:
			::Display *mX11Display;
		};
	}
}

#endif
