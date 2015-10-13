#include "../include/AnimaOSTimerManager.h"

AE::OS::TimerManager* AE::OS::TimerManager::mInstance = 0;

namespace AE
{
	namespace OS
	{
		TimerManager::TimerManager() : AE::Plugin(AE::PT_OS_TIMER_MANAGER) 
		{
		}

		TimerManager::~TimerManager()
		{
		}
	}
}
