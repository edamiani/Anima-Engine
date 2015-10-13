#ifndef __AE_OS_PROCESS_WIN32__
#define __AE_OS_PROCESS_WIN32__

#include "AnimaOSProcess.h"
#include "AnimaOSEventManagerWin32.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class ProcessWin32 : public AE::OS::Process
		{
		public:
			ProcessWin32();
			virtual ~ProcessWin32();

			bool dispatchNextMessage();
			void quit() { ::PostQuitMessage(0); }
			bool waitAndDispatchNextMessage();
			void yield() { ::Sleep(0); }
		};
	}
}

#endif