#ifndef __AE_OS_PROCESS_MANAGER_OSX__
#define __AE_OS_PROCESS_MANAGER_OSX__

#include "AnimaOSProcessManager.h"

namespace AE
{
	namespace OS
	{
		class ProcessManagerOSX : public AE::OS::ProcessManager
		{
		public:
			ProcessManagerOSX();
			~ProcessManagerOSX();

			AE::OS::Process* createProcess();
		};
	}
}

#endif