#ifndef __AE_OS_TIMER_PERIODIC_POCO__
#define __AE_OS_TIMER_PERIODIC_POCO__

#include "AnimaOSTimerPeriodic.h"

#include "Poco/Timer.h"

namespace AE
{
	namespace OS
	{
		class TimerPeriodicPoco : public AE::OS::TimerPeriodic
		{
		public:
			TimerPeriodicPoco(AE::ulong startInterval, AE::ulong periodicInterval, AE::OS::TimerListener *timerListener);
			~TimerPeriodicPoco();

			void restart();
			void start();
			void stop();

		private:
			/* Internal class to be used only by TimerPeriodicPoco */
			class TimerCallbackPoco
			{
			public:
				TimerCallbackPoco(AE::OS::TimerListener *timerListener) 
					: mAnimaListener(timerListener),
					  mPocoListener(*this, &AE::OS::TimerPeriodicPoco::TimerCallbackPoco::onInterval)
				{
				}

				~TimerCallbackPoco() {}

				void onInterval(Poco::Timer &pocoTimer) { mAnimaListener->onInterval(); }

				Poco::TimerCallback<AE::OS::TimerPeriodicPoco::TimerCallbackPoco> & _getCallback() { return mPocoListener; }
			private:
				AE::OS::TimerListener *mAnimaListener;
				Poco::TimerCallback<AE::OS::TimerPeriodicPoco::TimerCallbackPoco> mPocoListener;
			} mPocoCallback;

			Poco::Timer *mPocoTimer;
		};
	}
}

#endif