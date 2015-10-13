#ifndef __AE_OS_PROCESS_MANAGER_WIN32__
#define __AE_OS_PROCESS_MANAGER_WIN32__

#include "AnimaOSProcessManager.h"

namespace AE
{
	namespace OS
	{
		class ProcessManagerWin32 : public AE::OS::ProcessManager
		{
		public:
			ProcessManagerWin32();
			~ProcessManagerWin32();

			AE::OS::Process* createProcess();
		};
	}
}

#endif