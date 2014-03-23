#include "../include/AnimaMVCFrontControllerFSMOSX.h"
#include "../include/AnimaGraphicsManagerGL.h"
#include "../include/AnimaAIFSMMachine.h"
#include "../include/AnimaMVCControllerCommandEventLoopFSMOSX.h"
#include "../include/AnimaMVCControllerCommandRealTimeLoopFSMOSX.h"

#include <cassert>

namespace AE
{
	namespace MVC
	{
		FrontControllerFSMOSX::FrontControllerFSMOSX(char *windowTitle, AE::OS::WindowMetrics &windowMetrics, bool isFullScreen, bool isRealTime, AE::Graphics::RenderType renderType)
			: WindowOSX(windowTitle, windowMetrics, isFullScreen), mIsRealTime(isRealTime)
		{
			if(!mIsRealTime)
				mCommand = new AE::MVC::ControllerCommandEventLoopFSMOSX(this);
			else
				mCommand = new AE::MVC::ControllerCommandRealTimeLoopFSMOSX(this);

			mGraphicsManager = new AE::Graphics::ManagerGL();

			bool result = mGraphicsManager->initialize(this);
			assert(result);

			mDefaultView = new AE::MVC::View(mGraphicsManager);
		}

		FrontControllerFSMOSX::~FrontControllerFSMOSX()
		{
			delete mCommand;
		}
	}
}
