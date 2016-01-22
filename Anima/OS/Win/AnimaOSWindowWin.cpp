#include "AnimaOSWindowWin.h"
#include "AnimaOSEventQueueWin.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowWin::WindowWin(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc)
			: Window(windowTitle, windowDesc)
		{
			mIsFullScreen = false;

			//Converts windowTitle to Unicode
			int lenA = ::lstrlenA(windowTitle.c_str());
			int lenW;
			BSTR unicodeStr;
			// This time we'll only get the Unicode string's length
			lenW = ::MultiByteToWideChar(CP_ACP, 0, windowTitle.c_str(), lenA, 0, 0);
			unicodeStr = ::SysAllocStringLen(0, lenW);
			// Now we convert it
			::MultiByteToWideChar(CP_ACP, 0, windowTitle.c_str(), lenA, unicodeStr, lenW);

			WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_OWNDC | CS_HREDRAW | CS_VREDRAW, AE::OS::EventQueueWin::MsgProc, 0L, 0L,
							  ::GetModuleHandle(NULL), ::LoadIcon(0, IDI_APPLICATION), ::LoadCursor(0, IDC_ARROW), NULL, NULL,
							  unicodeStr, NULL };

			::RegisterClassEx(&wc);
			
			// Create the application's window
			RECT clientRect;
			clientRect.top = 100;
			clientRect.left = 100;
			clientRect.bottom = (LONG)(windowDesc.dimensions.y + 100);
			clientRect.right = (LONG)(windowDesc.dimensions.x + 100);
			AdjustWindowRectEx(&clientRect, WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE, NULL);

			/*mWindowMetrics.left = clientRect.left;
			mWindowMetrics.width = windowDesc.dimensions.x;
			mWindowMetrics.top = clientRect.top;
			mWindowMetrics.height = windowDesc.dimensions.y;*/
			//mWindowMetrics.setSurfaceFormat(surfaceFormat);

			mWindowHandle = ::CreateWindow(unicodeStr, unicodeStr,
				WS_OVERLAPPEDWINDOW, clientRect.top, clientRect.left, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
				::GetDesktopWindow(), NULL, wc.hInstance, NULL);

			::SetWindowLongPtr(mWindowHandle, GWLP_USERDATA, (ULONG_PTR)this);
			mHInstance = (HINSTANCE)(::GetWindowLongPtr(mWindowHandle, GWLP_HINSTANCE));

			//Releases the Unicode string
			::SysFreeString(unicodeStr);

			//mInputContext = new AE::Input::ContextDX9(this);
		}

		WindowWin::~WindowWin() 
		{
			::DestroyWindow(mWindowHandle);

			//delete mInputContext;
			//mInputContext = 0;
		}

		size_t WindowWin::getWindowHandle() 
		{
			size_t winHandle;
			HWND *pHwnd = (HWND*)(&winHandle);
			*pHwnd = mWindowHandle;
			return winHandle;
		}

		void WindowWin::render()
		{
			::ValidateRect(mWindowHandle, NULL);
		}
	}
}