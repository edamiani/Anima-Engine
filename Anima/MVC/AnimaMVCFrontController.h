#ifndef __AE_MVC_FRONT_CONTROLLER__
#define __AE_MVC_FRONT_CONTROLLER__

#include "AnimaMVCController.h"
#include "AnimaMVCControllerCommand.h"
#include "AnimaMVCView.h"

namespace AE
{
	namespace MVC
	{
		class FrontController : public AE::MVC::Controller
		{
		public:
			FrontController() : mCommand(0), mDefaultView(0) {  }
			virtual ~FrontController() {  }

			virtual void execute() {  }

		protected:
			AE::MVC::ControllerCommand *mCommand;
			AE::MVC::View *mDefaultView;
		};
	}
}

#endif