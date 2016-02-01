#ifndef __AE_OS_TIMER_MANAGER__
#define __AE_OS_TIMER_MANAGER__

#include "Anima/Plugin.h"

namespace AE
{
	namespace OS
	{
		class TimerFactory;

		class TimerManager : public AE::Plugin
		{
		public:
			TimerManager();
			virtual ~TimerManager();

			static AE::OS::TimerManager* getInstance() { assert(mInstance != 0); return mInstance; }

			AE::OS::TimerFactory* getTimerFactory() { return mTimerFactory; }

		protected:
			static AE::OS::TimerManager *mInstance;

			AE::OS::TimerFactory *mTimerFactory;
		};
	}
}

#endif
