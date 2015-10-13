#include "../include/AnimaOSTimerManagerPoco.h"

#include "../include/AnimaOSTimerFactoryPoco.h"

namespace AE
{
	namespace OS
	{
		TimerManagerPoco::TimerManagerPoco() 
		{
			mInstance = this;
		}

		TimerManagerPoco::~TimerManagerPoco()
		{
			mInstance = 0;
		}

		bool TimerManagerPoco::install(AE::uint options)
		{
			if(mParent != 0)
			{
				mTimerFactory = new AE::OS::TimerFactoryPoco();

				mIsInstalled = true;

				return true;
			}
			else
				return false;
		}

		bool TimerManagerPoco::uninstall()
		{
			delete mTimerFactory;
			mTimerFactory = 0;

			mIsInstalled = false;

			return true;
		}
	}
}