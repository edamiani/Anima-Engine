#ifndef __AE_MVC_CONTROLLER_COMMAND_REAL_TIME_LOOP_FSM_WIN32__
#define __AE_MVC_CONTROLLER_COMMAND_REAL_TIME_LOOP_FSM_WIN32__

#include "AnimaMVCControllerCommand.h"
#include "AnimaMVCFrontControllerFSMWin32.h"

namespace AE
{
	namespace MVC
	{
		class ControllerCommandRealTimeLoopFSMWin32 : public AE::MVC::ControllerCommand
		{
		public:
			ControllerCommandRealTimeLoopFSMWin32(AE::MVC::FrontControllerFSMWin32 *frontControllerFSM) : mFrontControllerFSM(frontControllerFSM) {}
			virtual ~ControllerCommandRealTimeLoopFSMWin32() {}

			void execute()
			{
				/*while(mFrontControllerFSM->dispatchNextMessage())
				{
					mFrontControllerFSM->updateMachine(0.0);
				}*/
			}

		private:
			AE::MVC::FrontControllerFSMWin32 *mFrontControllerFSM;
		};
	}
}

#endif