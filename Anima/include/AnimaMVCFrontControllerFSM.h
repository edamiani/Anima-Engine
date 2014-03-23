#ifndef __AE_MVC_FRONT_CONTROLLER_FSM__
#define __AE_MVC_FRONT_CONTROLLER_FSM__

#include "AnimaAIFSMMachine.h"
#include "AnimaMVCFrontController.h"

namespace AE
{
	namespace MVC
	{
		class FrontControllerFSM : public AE::MVC::FrontController, public AE::AI::FSMMachine
		{
		public:
			FrontControllerFSM() {  }
			virtual ~FrontControllerFSM() {  }

			virtual void execute() { updateMachine(0.0f); }
		};
	}
}

#endif