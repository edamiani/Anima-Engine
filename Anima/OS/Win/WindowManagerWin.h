#ifndef __AE_OS_WINDOW_MANAGER_WIN__
#define __AE_OS_WINDOW_MANAGER_WIN__

#include "Anima/OS/WindowManager.h"

#include "Anima/Platform.h"
#include "Anima/Types.h"

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
		class WindowManagerWin : public AE::OS::WindowManager
		{
		public:
			WindowManagerWin();
			WindowManagerWin(AE::Graphics::Device::Manager *deviceManager);
			virtual ~WindowManagerWin();

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