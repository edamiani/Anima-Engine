#include "Anima/Platform.h"
#include "Anima/OS/ProcessManager.h"

//#ifdef AE_PLATFORM_WIN32
//	#include "Anima/OS/ProcessManagerWin32.h"
//	#include "Anima/OS/ProcessWin32.h"
//#endif

#include <ctime>

AE::OS::ProcessManager* AE::OS::ProcessManager::mInstance = 0;
AE::OS::Process* AE::OS::ProcessManager::mMainProcess = 0;

namespace AE
{
	namespace OS
	{
		AE::OS::ProcessManager* ProcessManager::initialize()
		{
			srand(time(0));

		#ifdef AE_PLATFORM_WIN32
			mInstance = new AE::OS::ProcessManagerWin32();
			mMainProcess = new AE::OS::ProcessWin32();
		#endif

			return mInstance;
		}

		void ProcessManager::shutdown()
		{
			if(mMainProcess)
			{
				mMainProcess->quit();
				delete mMainProcess;
				mMainProcess = 0;
			}

			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}
	}
}