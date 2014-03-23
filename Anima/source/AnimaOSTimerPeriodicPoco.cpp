#include "../include/AnimaOSTimerPeriodicPoco.h"

namespace AE
{
	namespace OS
	{
		TimerPeriodicPoco::TimerPeriodicPoco(AE::ulong startInterval, AE::ulong periodicInterval, AE::OS::TimerListener *timerListener)
				: TimerPeriodic(startInterval, periodicInterval), mPocoCallback(timerListener)
		{
			mPocoTimer = new Poco::Timer(startInterval, periodicInterval);
		}

		TimerPeriodicPoco::~TimerPeriodicPoco() {  }

		void TimerPeriodicPoco::restart() 
		{ 
			mPocoTimer->restart(); 
		}

		void TimerPeriodicPoco::start() 
		{
			mPocoTimer->start(mPocoCallback._getCallback()); 
		}

		void TimerPeriodicPoco::stop() 
		{ 
			mPocoTimer->stop(); 
		}
	}
}