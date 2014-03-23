#ifndef __AE_MVC_CONTROLLER_COMMAND_REAL_TIME_LOOP__
#define __AE_MVC_CONTROLLER_COMMAND_REAL_TIME_LOOP__

#include "AnimaMVCControllerCommand.h"
#include "AnimaOSWindow.h"

namespace AE
{
	namespace MVC
	{
		class ControllerCommandRealTimeLoop : public AE::MVC::ControllerCommand
		{
		public:
			ControllerCommandRealTimeLoop(AE::OS::Window *window) : mWindow(window) {}
			virtual ~ControllerCommandRealTimeLoop() {}

			void execute()
			{
				while(mWindow->dispatchNextMessage())
				{
					innerLoop();
				}
			}

			virtual void innerLoop() = 0;

		private:
			AE::OS::Window *mWindow;
		};
	}
}

#endif