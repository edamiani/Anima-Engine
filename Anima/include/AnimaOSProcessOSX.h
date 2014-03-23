#ifndef __AE_OS_PROCESS_OSX__
#define __AE_OS_PROCESS_OSX__

#include "AnimaOSProcess.h"
#include "AnimaOSEventManagerOSX.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class ProcessOSX : public AE::OS::Process
		{
		public:
			ProcessOSX();
			virtual ~ProcessOSX();

			bool dispatchNextMessage();
			void quit() { /*::PostQuitMessage(0);*/ }
			bool waitAndDispatchNextMessage();
			void yield() { /*::Sleep(0);*/ }
		};
	}
}

#endif