#ifndef __AE_MVC_CONTROLLER_COMMAND_EVENT_LOOP_FSM_WIN32__
#define __AE_MVC_CONTROLLER_COMMAND_EVENT_LOOP_FSM_WIN32__

#include "AnimaMVCControllerCommand.h"
#include "AnimaMVCFrontControllerFSMWin32.h"

namespace AE
{
	namespace MVC
	{
		class ControllerCommandEventLoopFSMWin32 : public AE::MVC::ControllerCommand
		{
		public:
			ControllerCommandEventLoopFSMWin32(AE::MVC::FrontControllerFSMWin32 *frontControllerFSM) : mFrontControllerFSM(frontControllerFSM) {}
			virtual ~ControllerCommandEventLoopFSMWin32() {}

			void execute()
			{
				/*while(mFrontControllerFSM->waitAndDispatchNextMessage())
					mFrontControllerFSM->updateMachine(0.0);*/
			}

		private:
			AE::MVC::FrontControllerFSMWin32 *mFrontControllerFSM;
		};
	}
}

#endif