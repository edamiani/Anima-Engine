#ifndef __AE_OS_PROCESS_LINUX__
#define __AE_OS_PROCESS_LINUX__

#include "AnimaOSProcess.h"
#include "AnimaOSEventManagerLinux.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class ProcessLinux : public AE::OS::Process
		{
		public:
			ProcessLinux();
			virtual ~ProcessLinux();

			bool dispatchNextMessage();
			void quit() { ::PostQuitMessage(0); }
			bool waitAndDispatchNextMessage();
			void yield() {
//			    ::Sleep(0);
            }
		};
	}
}

#endif
