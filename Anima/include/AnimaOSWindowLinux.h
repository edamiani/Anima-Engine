#ifndef __AE_OS_WINDOW_LINUX__
#define __AE_OS_WINDOW_LINUX__

#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSWindow.h"
#include "AnimaPlatform.h"

#include <X11/cursorfont.h>
#include <X11/Xlib.h>
//#include <X11/Xos.h>
#include <X11/Xutil.h>

#include <string>

namespace AE
{
	namespace OS
	{
		class WindowLinux : public Window
		{
		public:
			WindowLinux(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc);
			~WindowLinux();

			void	close();
			size_t  getWindowHandle() { return 0; } // useless in Linux
			void	render() {}
			void	show();

			::Window _getX11Window() { return mWindow; }

		protected:
			long 	 mScreenID;
			::Window mWindow;
		};
	}
}

#endif
