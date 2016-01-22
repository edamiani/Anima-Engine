#ifndef __AE_OS_WINDOW_MANAGER_SDL__
#define __AE_OS_WINDOW_MANAGER_SDL__

#include "../AnimaOSWindowManager.h"

#include "Anima/AnimaPlatform.h"
#include "Anima/AnimaTypes.h"

//#include "SDL.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Manager;
		}
	}

	namespace OS
	{
		class WindowManagerSdl : public AE::OS::WindowManager
		{
		public:
			WindowManagerSdl();
			WindowManagerSdl(AE::Graphics::Device::Manager *deviceManager);
			~WindowManagerSdl();

			bool install(AE::uint options);
			bool uninstall();

			AE::OS::Window* createWindow(const std::string &windowTitle, AE::OS::WindowDesc &windowDesc);
			AE::OS::Window* createWindow(const std::string &windowTitle, AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Context *deviceContext);
			void destroyWindow(AE::OS::Window *window);

		private:
		};
	}
}

#endif