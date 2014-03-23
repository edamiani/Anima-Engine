#ifndef __AE_OS_APPLICATION_WIN32__
#define __AE_OS_APPLICATION_WIN32__

#include "AnimaOSApplication.h"
#include "AnimaOSEventManagerWin32.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class ApplicationWin32 : public AE::OS::Application
		{
		public:
			ApplicationWin32();
			virtual ~ApplicationWin32();

			bool dispatchNextMessage();
			void quit() { ::PostQuitMessage(0); }
			bool waitAndDispatchNextMessage();
			void yield() { ::Sleep(0); }
		};
	}
}

#endif