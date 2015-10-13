#ifndef __AE_MVC_FRONT_CONTROLLER_OSX__
#define __AE_MVC_FRONT_CONTROLLER_OSX__

#include "AnimaMVCFrontControllerFSM.h"
#include "AnimaOSWindowOSX.h"

namespace AE
{
	namespace MVC
	{
		class FrontControllerFSMOSX : public AE::MVC::FrontControllerFSM, public AE::OS::WindowOSX
		{
		public:
			FrontControllerFSMOSX(char *windowTitle, AE::OS::WindowMetrics &windowMetrics, bool isFullScreen = false, bool isRealTime = false, AE::Graphics::RenderType renderType = AE::Graphics::RT_OPENGL);
			virtual ~FrontControllerFSMOSX();

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