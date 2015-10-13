#ifndef __AE_OS_MANAGER_WIN32__
#define __AE_OS_MANAGER_WIN32__

#include "AnimaOSManager.h"

#include <windows.h>

namespace AE
{
	namespace OS
	{
		class ManagerLinux : public AE::OS::Manager
		{
		public:
			ManagerLinux() {}
			virtual ~ManagerLinux() {}

			void yield() { Sleep(0); }
		};
	}
}

#endif
