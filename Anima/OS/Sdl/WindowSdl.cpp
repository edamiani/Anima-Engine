#include "WindowSdl.h"
#include "EventQueueSdl.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowSdl::WindowSdl(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc)
			: Window(windowTitle, windowDesc)
		{
			mIsFullScreen = false;

			mWindow = SDL_CreateWindow(windowTitle.c_str(), windowDesc.position.x, windowDesc.position.y,
									   windowDesc.dimensions.x, windowDesc.dimensions.y, SDL_WINDOW_HIDDEN);

			SDL_SetWindowData(mWindow, "AnimaWindow", this);
		}

		WindowSdl::~WindowSdl()
		{
			SDL_DestroyWindow(mWindow);
		}

		size_t WindowSdl::getWindowHandle()
		{
			/*size_t winHandle;
			HWND *pHwnd = (HWND*)(&winHandle);
			*pHwnd = mWindowHandle;
			return winHandle;*/

			return 0;
		}

		void WindowSdl::render()
		{

		}
	}
}