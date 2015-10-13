#ifndef __AE_OS_TIMER_FACTORY_POCO__
#define __AE_OS_TIMER_FACTORY_POCO__

#include "AnimaOSTimerFactory.h"

namespace AE
{
	namespace OS
	{
		class TimerFactoryPoco : public AE::OS::TimerFactory
		{
		public:
			TimerFactoryPoco() {}
			virtual ~TimerFactoryPoco() {}

			AE::OS::TimerPeriodic* createTimerPeriodic(AE::ulong startInterval, AE::ulong periodicInterval, AE::OS::TimerListener *timerListener);
			AE::OS::TimerSimple* createTimerSimple();
			void destroyTimer(AE::OS::Timer* timer);
		};
	}
}

#endif
