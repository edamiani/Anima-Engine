#include "../include/AnimaOSTimerFactoryPoco.h"

#include "../include/AnimaOSTimerPeriodicPoco.h"

namespace AE
{
	namespace OS
	{
		AE::OS::TimerPeriodic* TimerFactoryPoco::createTimerPeriodic(AE::ulong startInterval, AE::ulong periodicInterval, AE::OS::TimerListener *timerListener)
		{
			return new AE::OS::TimerPeriodicPoco(startInterval, periodicInterval, timerListener);
		}

		AE::OS::TimerSimple* TimerFactoryPoco::createTimerSimple()
		{
			return 0;
		}

		void destroyTimer(AE::OS::Timer* timer)
		{
			if(timer)
				delete timer;
		}
	}
}