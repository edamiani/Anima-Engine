#include "../include/AnimaOSProcessLinux.h"
#include "../include/AnimaOSWindowLinux.h"
#include "../include/AnimaGraphicsManager.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		ProcessLinux::ProcessLinux()
		{
		}

		ProcessLinux::~ProcessLinux()
		{
		}

		bool ProcessLinux::dispatchNextMessage()
		{
//			MSG message;
//			::PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE);
//			if(message.message != WM_QUIT)
//			{
//				::TranslateMessage(&message);
//				::DispatchMessage(&message);
//				return true;
//			}
//			else
//				return false;
            return true;
		}

		bool ProcessLinux::waitAndDispatchNextMessage()
		{
//			MSG message;
//			BOOL result = ::GetMessage(&message, NULL, NULL, NULL);
//
//			if(result > 0)
//			{
//				::TranslateMessage(&message);
//				::DispatchMessage(&message);
//				return true;
//			}
//			else
//			{
//				//DWORD error = ::GetLastError();
//				return false;
//			}
            return true;
		}
	}
}
