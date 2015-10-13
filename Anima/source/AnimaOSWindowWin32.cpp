#include "../include/AnimaOSWindowWin32.h"
#include "../include/AnimaOSEventManagerWin32.h"
#include "../include/AnimaGraphicsDrawingContext.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaInputContextDX9.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowWin32::WindowWin32(const std::string &windowTitle, const AE::Math::Point2 &dimensions)
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

			WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_OWNDC | CS_HREDRAW | CS_VREDRAW, AE::OS::EventManagerWin32::MsgProc, 0L, 0L,
							  ::GetModuleHandle(NULL), ::LoadIcon(0, IDI_APPLICATION), ::LoadCursor(0, IDC_ARROW), NULL, NULL,
							  unicodeStr, NULL };

			::RegisterClassEx(&wc);
			
			// Create the application's window
			RECT clientRect;
			clientRect.top = 100;
			clientRect.left = 100;
			clientRect.bottom = (LONG)(dimensions.y + 100);
			clientRect.right = (LONG)(dimensions.x + 100);
			AdjustWindowRectEx(&clientRect, WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX, FALSE, NULL);

			mWindowMetrics.left = clientRect.left;
			mWindowMetrics.width = dimensions.x;
			mWindowMetrics.top = clientRect.top;
			mWindowMetrics.height = dimensions.y;
			//mWindowMetrics.setSurfaceFormat(surfaceFormat);

			mWindowHandle = ::CreateWindow(unicodeStr, unicodeStr,
				WS_OVERLAPPEDWINDOW, clientRect.top, clientRect.left, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top,
				::GetDesktopWindow(), NULL, wc.hInstance, NULL);

			::SetWindowLongPtr(mWindowHandle, GWLP_USERDATA, (ULONG_PTR)this);
			mHInstance = (HINSTANCE)(::GetWindowLongPtr(mWindowHandle, GWL_HINSTANCE));

			//Releases the Unicode string
			::SysFreeString(unicodeStr);

			mInputContext = new AE::Input::ContextDX9(this);
		}

		WindowWin32::~WindowWin32() 
		{
			::DestroyWindow(mWindowHandle);

			delete mInputContext;
			mInputContext = 0;
		}

		size_t WindowWin32::getWindowHandle() 
		{
			size_t winHandle;
			HWND *pHwnd = (HWND*)(&winHandle);
			*pHwnd = mWindowHandle;
			return winHandle;
		}

		void WindowWin32::render()
		{
			::ValidateRect(mWindowHandle, NULL);
		}
	}
}