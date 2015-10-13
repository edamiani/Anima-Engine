#ifndef __AE_OS_TIMER_LISTENER__
#define __AE_OS_TIMER_LISTENER__

#include "AnimaTypes.h"

namespace AE
{
	namespace OS
	{
		class TimerListener
		{
		public:
			TimerListener() {}
			virtual ~TimerListener() {}

			virtual void onInterval() = 0;
		};
	}
}

#endif