#ifndef __AE_MVC_CONTROLLER_FSM__
#define __AE_MVC_CONTROLLER_FSM__

#include "AnimaAIFSMMachine.h"
#include "AnimaMVCController.h"

namespace AE
{
	namespace MVC
	{
		class ControllerFSM : public AE::MVC::Controller, public AE::AI::FSMMachine
		{
		public:
			ControllerFSM() {  }
			virtual ~ControllerFSM() {  }

			virtual void execute() { updateMachine(0.0f); }
		};
	}
}

#endif