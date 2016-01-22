#ifndef __AE_OS_WINDOW_WIN__
#define __AE_OS_WINDOW_WIN__

#include "../AnimaOSWindow.h"
#include "../../AnimaPlatform.h"

#include "SDL.h"

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
		class WindowSdl : public Window
		{
		public:
			WindowSdl(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc);
			~WindowSdl();

			void	close() { ::DestroyWindow(mWindowHandle); }
			size_t	getWindowHandle();
			void	render();
			void	show() { SDL_ShowWindow(mWindow); }

			HWND _getWindowHandle() { return mWindowHandle; }
			HINSTANCE _getHInstance() { return mHInstance; }

		protected:
			HWND	mWindowHandle;
			HINSTANCE mHInstance;
			SDL_Window *mWindow;
		};
	}
}

#endif