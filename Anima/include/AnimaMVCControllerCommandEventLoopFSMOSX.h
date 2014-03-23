#ifndef __AE_MVC_CONTROLLER_COMMAND_EVENT_LOOP_FSM_OSX__
#define __AE_MVC_CONTROLLER_COMMAND_EVENT_LOOP_FSM_OSX__

#include "AnimaMVCControllerCommand.h"
#include "AnimaMVCFrontControllerFSMOSX.h"

namespace AE
{
	namespace MVC
	{
		class ControllerCommandEventLoopFSMOSX : public AE::MVC::ControllerCommand
		{
		public:
			ControllerCommandEventLoopFSMOSX(AE::MVC::FrontControllerFSMOSX *frontControllerFSM) : mFrontControllerFSM(frontControllerFSM) {}
			virtual ~ControllerCommandEventLoopFSMWin32() {}

			void execute()
			{
				while(mFrontControllerFSM->waitAndDispatchNextMessage())
					mFrontControllerFSM->updateMachine(0.0);
			}

		private:
			AE::MVC::FrontControllerFSMOSX *mFrontControllerFSM;
		};
	}
}

#endif