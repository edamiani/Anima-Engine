#ifndef __AE_OS_MANAGER_OSX__
#define __AE_OS_MANAGER_OSX__

#include "AnimaOSManager.h"

namespace AE
{
	namespace OS
	{
		class ManagerOSX : public AE::OS::Manager
		{
		public:
			ManagerOSX() {}
			virtual ~ManagerOSX() {}

			void yield() { Sleep(0); }
		};
	}
}

#endif