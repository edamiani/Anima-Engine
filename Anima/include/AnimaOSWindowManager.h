#ifndef __AE_OS_WINDOW_MANAGER__
#define __AE_OS_WINDOW_MANAGER__

#include "AnimaOSEventQueue.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSEnums.h"
#include "AnimaOSWindowDesc.h"
#include "AnimaPlatform.h"
#include "AnimaPlugin.h"
#include "AnimaSingleton.h"
#include "AnimaTypes.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Driver;
		}
	}

	namespace OS
	{
		class Window;

		class WindowManager : public AE::Plugin
		{
		public:
			WindowManager() : AE::Plugin(AE::PT_OS_WINDOW_MANAGER) {}
			virtual ~WindowManager();

			static AE::OS::WindowManager*	getInstance() { assert(mInstance != 0); return mInstance; }

			//virtual bool					initialize(AE::uint options) = 0;
			//virtual bool					shutdown() = 0;

			virtual AE::OS::Window*			createWindow(const std::string &windowTitle, AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Driver *deviceDriver) = 0;
			virtual void 					destroyWindow(AE::OS::Window *window) = 0;
			AE::OS::EventQueue*				getEventQueue() { return mEventQueue; }
			std::list<AE::OS::Window *>&	getWindowList() { return mWindows; }


		protected:
			static AE::OS::WindowManager	*mInstance;

			AE::OS::EventQueue				*mEventQueue;
			std::list<AE::OS::Window *>		mWindows;
		};
	}
}

#endif
