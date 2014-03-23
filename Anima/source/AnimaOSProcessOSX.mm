#include "../include/AnimaOSProcessOSX.h"
#include "../include/AnimaOSWindowOSX.h"
#include "../include/AnimaGraphicsManager.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		ProcessOSX::ProcessOSX()
		{
		}

		ProcessOSX::~ProcessOSX()
		{
		}

		bool ProcessOSX::dispatchNextMessage()
		{
/*			MSG message;
			::PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE);
			if(message.message != WM_QUIT)
			{
				::TranslateMessage(&message);
				::DispatchMessage(&message);
				return true;
			}
			else
				return false;
 */		return true;
		}

		bool ProcessOSX::waitAndDispatchNextMessage()
		{
/*			MSG message;
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
 */		return true;
		}
	}
}