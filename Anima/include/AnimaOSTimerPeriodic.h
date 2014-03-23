#ifndef __AE_OS_TIMER_PERIODIC__
#define __AE_OS_TIMER_PERIODIC__

#include "AnimaOSTimer.h"
#include "AnimaOSTimerListener.h"

namespace AE
{
	namespace OS
	{
		class TimerPeriodic : public AE::OS::Timer
		{
		public:
			TimerPeriodic(AE::ulong startInterval, AE::ulong periodicInterval)
				: mStartInterval(startInterval), mPeriodicInterval(periodicInterval) {}

			~TimerPeriodic() { }

			virtual void restart() = 0;
			virtual void start() = 0;
			virtual void stop() = 0;

		protected:
			AE::ulong mPeriodicInterval;
			AE::ulong mStartInterval;
		};
	}
}

#endif