#include "../include/AnimaMVCFrontControllerFSMWin32.h"
#include "../include/AnimaGraphicsManagerDX9.h"
#include "../include/AnimaGraphicsManagerGL.h"
#include "../include/AnimaAIFSMMachine.h"
#include "../include/AnimaMVCControllerCommandEventLoopFSMWin32.h"
#include "../include/AnimaMVCControllerCommandRealTimeLoopFSMWin32.h"

#include <cassert>

namespace AE
{
	namespace MVC
	{
		FrontControllerFSMWin32::FrontControllerFSMWin32(AE::uint8 id, char *windowTitle, AE::OS::WindowMetrics &windowMetrics, bool isFullScreen, bool isRealTime, AE::Graphics::RenderType renderType)
			: WindowWin32(id, windowTitle, windowMetrics, isFullScreen), mIsRealTime(isRealTime)
		{
			if(!mIsRealTime)
				mCommand = new AE::MVC::ControllerCommandEventLoopFSMWin32(this);
			else
				mCommand = new AE::MVC::ControllerCommandRealTimeLoopFSMWin32(this);

			if(renderType == AE::Graphics::RT_DIRECT3D9)
				mGraphicsManager = new AE::Graphics::ManagerDX9();
			else
			{
				mGraphicsManager = new AE::Graphics::ManagerGL();
			}

			bool result = mGraphicsManager->initialize(this);
			assert(result);

			mDefaultView = new AE::MVC::View(mGraphicsManager);
		}

		FrontControllerFSMWin32::~FrontControllerFSMWin32()
		{
			delete mCommand;
		}
	}
}
