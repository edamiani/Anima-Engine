#ifndef __AE_OS_TIMER_FACTORY__
#define __AE_OS_TIMER_FACTORY__

#include "AnimaTypes.h"

namespace AE
{
	namespace OS
	{
		class Timer;
		class TimerPeriodic;
		class TimerSimple;
		class TimerListener;

		class TimerFactory
		{
		public:
			TimerFactory() {}
			virtual ~TimerFactory() {}

			virtual AE::OS::TimerPeriodic* createTimerPeriodic(AE::ulong startInterval, AE::ulong periodicInterval, AE::OS::TimerListener *timerListener) = 0;
			virtual AE::OS::TimerSimple* createTimerSimple() = 0;
		};
	}
}

#endif
