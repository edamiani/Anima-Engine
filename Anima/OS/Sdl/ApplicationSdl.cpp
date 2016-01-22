#include "../include/AnimaOSApplicationWin32.h"
#include "../include/AnimaOSWindowWin32.h"
#include "../include/AnimaGraphicsManager.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		ApplicationWin32::ApplicationWin32()
		{
			mInstance = this;
			new AE::OS::EventManagerWin32();
		}

		ApplicationWin32::~ApplicationWin32()
		{
			std::map<AE::uint8, AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
				delete (*i).second;
			mWindows.clear();

			mInstance = 0;
			delete AE::OS::EventManagerWin32::getInstance();
		}

		bool ApplicationWin32::dispatchNextMessage()
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

		bool ApplicationWin32::waitAndDispatchNextMessage()
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