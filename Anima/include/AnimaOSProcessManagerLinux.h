#ifndef __AE_OS_PROCESS_MANAGER_LINUX__
#define __AE_OS_PROCESS_MANAGER_LINUX__

#include "AnimaOSProcessManager.h"

namespace AE
{
	namespace OS
	{
		class ProcessManagerLinux: public AE::OS::ProcessManager
		{
		public:
			ProcessManagerLinux();
			~ProcessManagerLinux();

			AE::OS::Process* createProcess();
		};
	}
}

#endif
