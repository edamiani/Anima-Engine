#ifndef __AE_OS_WINDOW_WIN__
#define __AE_OS_WINDOW_WIN__

#include "../AnimaOSWindow.h"
#include "../../AnimaPlatform.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Context;
		}
	}

	namespace OS
	{
		class WindowWin : public Window
		{
		public:
			WindowWin(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc);
			~WindowWin();

			void	close() { ::DestroyWindow(mWindowHandle); }
			size_t	getWindowHandle();
			void	render();
			void	show() { ::ShowWindow(mWindowHandle, SW_SHOWNORMAL); }

			HWND _getWindowHandle() { return mWindowHandle; }
			HINSTANCE _getHInstance() { return mHInstance; }

		protected:
			HWND	mWindowHandle;
			HINSTANCE mHInstance;
		};
	}
}

#endif