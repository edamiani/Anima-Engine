#ifndef __AE_OS_WINDOW_WIN32__
#define __AE_OS_WINDOW_WIN32__

#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSWindow.h"
#include "AnimaPlatform.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class DeviceWin32;
		class Surface;
	}

	namespace OS
	{
		class WindowWin32 : public Window
		{
		public:
			WindowWin32(const std::string &windowTitle, const AE::Math::Point2 &dimensions);
			~WindowWin32();

			void	close() { ::DestroyWindow(mWindowHandle); }
			//bool	dispatchNextMessage();
			size_t	getWindowHandle();
			void	render();
			void	show() { ::ShowWindow(mWindowHandle, SW_SHOWNORMAL); }
			//bool	waitAndDispatchNextMessage();

			// Window events
			virtual void onClose() {  }
			virtual void onDestroy() {  }
			virtual void onDisplayChange() {  }
			virtual void onMove() {  }
			virtual void onResize() {  }

			HWND _getWindowHandle() { return mWindowHandle; }
			HINSTANCE _getHInstance() { return mHInstance; }

		protected:
			HWND	mWindowHandle;
			HINSTANCE mHInstance;
		};

		//LRESULT WINAPI WindowWin32MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	}
}

#endif