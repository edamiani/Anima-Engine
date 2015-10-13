#ifndef __AE_OS_TIMER_MANAGER_POCO__
#define __AE_OS_TIMER_MANAGER_POCO__

#include "AnimaOSTimerManager.h"

namespace AE
{
	namespace OS
	{
		class TimerManagerPoco : public AE::OS::TimerManager
		{
		public:
			TimerManagerPoco();
			virtual ~TimerManagerPoco();

			bool install(AE::uint options);
			bool uninstall();

		protected:

		};
	}
}

#endif
