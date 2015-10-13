#include "../include/AnimaOSProcessWin32.h"
#include "../include/AnimaOSWindowWin32.h"
#include "../include/AnimaGraphicsManager.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		ProcessWin32::ProcessWin32()
		{
		}

		ProcessWin32::~ProcessWin32()
		{
		}

		bool ProcessWin32::dispatchNextMessage()
		{
			MSG message;
			::PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE);
			if(message.message != WM_QUIT)
			{
				::TranslateMessage(&message);
				::DispatchMessage(&message);
				return true;
			}
			else
				return false;
		}

		bool ProcessWin32::waitAndDispatchNextMessage()
		{
			MSG message;
			BOOL result = ::GetMessage(&message, NULL, NULL, NULL);

			if(result > 0)
			{
				::TranslateMessage(&message);
				::DispatchMessage(&message);
				return true;
			}
			else
			{
				//DWORD error = ::GetLastError();
				return false;
			}
		}
	}
}