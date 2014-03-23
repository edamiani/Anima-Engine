#ifndef __AE_MVC_FRONT_CONTROLLER_WIN32__
#define __AE_MVC_FRONT_CONTROLLER_WIN32__

#include "AnimaMVCFrontControllerFSM.h"
#include "AnimaOSWindow.h"

namespace AE
{
	namespace MVC
	{
		class FrontControllerFSMWin32 : public AE::MVC::FrontControllerFSM, public AE::OS::WindowWin32
		{
		public:
			FrontControllerFSMWin32(char *windowTitle, AE::OS::WindowMetrics &windowMetrics, bool isFullScreen = false, bool isRealTime = false, AE::Graphics::RenderType renderType = AE::Graphics::RT_DIRECT3D9);
			virtual ~FrontControllerFSMWin32();

			void execute() { mCommand->execute(); }

			virtual void onClose() {  }
			virtual void onDisplayChange() {  }
			virtual void onMove() {  }
			virtual void onResize() {  }

		protected:
			bool mIsRealTime;
		};
	}
}

#endif