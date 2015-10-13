#ifndef __AE_OS_PROCESS_MANAGER__
#define __AE_OS_PROCESS_MANAGER__

//#include "AnimaSingleton.h"

#include "AnimaPlatform.h"
#include "AnimaOSEnums.h"
#include "AnimaOSProcess.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		class ProcessManager
		{
		public:
			ProcessManager() {}
			virtual ~ProcessManager() { mInstance = 0; }

			static AE::OS::ProcessManager*	getInstance() { assert(mInstance != 0); return mInstance; }
			static AE::OS::ProcessManager*	initialize();
			static void						shutdown();

			virtual AE::OS::Process*		createProcess() = 0;
			AE::OS::Process*				getMainProcess() { return mMainProcess; }

		protected:
			static AE::OS::ProcessManager	*mInstance;
			static AE::OS::Process			*mMainProcess;
		};
	}
}

#endif
