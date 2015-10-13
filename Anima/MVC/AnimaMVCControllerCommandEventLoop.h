#ifndef __AE_MVC_CONTROLLER_COMMAND_EVENT_LOOP__
#define __AE_MVC_CONTROLLER_COMMAND_EVENT_LOOP__

#include "AnimaMVCControllerCommand.h"
#include "AnimaOSWindow.h"

namespace AE
{
	namespace MVC
	{
		class ControllerCommandEventLoop : public AE::MVC::ControllerCommand
		{
		public:
			ControllerCommandEventLoop(AE::OS::Window *window) : mWindow(window) {}
			virtual ~ControllerCommandEventLoop() {}

			void execute()
			{
				while(mWindow->waitAndDispatchNextMessage())
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