#ifndef __AE_MVC_CONTROLLER_COMMAND_REAL_TIME_LOOP_FSM_OSX__
#define __AE_MVC_CONTROLLER_COMMAND_REAL_TIME_LOOP_FSM_OSX__

#include "AnimaMVCControllerCommand.h"
#include "AnimaMVCFrontControllerFSMOSX.h"

namespace AE
{
	namespace MVC
	{
		class ControllerCommandRealTimeLoopFSMOSX : public AE::MVC::ControllerCommand
		{
		public:
			ControllerCommandRealTimeLoopFSMOSX(AE::MVC::FrontControllerFSMOSX *frontControllerFSM) : mFrontControllerFSM(frontControllerFSM) {}
			virtual ~ControllerCommandRealTimeLoopFSMOSX() {}

			void execute()
			{
				while(mFrontControllerFSM->dispatchNextMessage())
				{
					mFrontControllerFSM->updateMachine(0.0);
				}
			}

		private:
			AE::MVC::FrontControllerFSMOSX *mFrontControllerFSM;
		};
	}
}

#endif