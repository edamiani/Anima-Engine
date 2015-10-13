#include "../include/AnimaMVCFrontController.h"

namespace AE
{
	namespace MVC
	{
		FrontController::FrontController(AE::OS::Window *window, bool realTime)
				: mWindow(window)
		{
			if(!realTime)
				mCommand = new AE::MVC::ControllerCommandEventLoop(mWindow);
			else
				mCommand = new AE::MVC::ControllerCommandRealTimeLoop(mWindow);
		}

		FrontController::~FrontController() 
		{
			mWindow = 0;
			delete mCommand;
		}
	}
}