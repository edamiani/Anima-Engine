#include "WindowManagerSdl.h"

#include "EventQueueSdl.h"
#include "WindowSdl.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{

	}

	namespace OS
	{
		WindowManagerSdl::WindowManagerSdl()
		{
			mInstance = this;
		}

		WindowManagerSdl::~WindowManagerSdl()
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				delete *i;
			}

			mInstance = 0;
		}

		bool WindowManagerSdl::install(AE::uint options)
		{
			SDL_InitSubSystem(SDL_INIT_VIDEO);
			SDL_InitSubSystem(SDL_INIT_EVENTS);

			if(mParent != 0)
			{
				mEventQueue = new AE::OS::EventQueueSdl();

				mIsInstalled = true;

				return true;
			}
			else
				return false;
		}

		bool WindowManagerSdl::uninstall()
		{
			delete mEventQueue;
			mEventQueue = 0;

			if(SDL_WasInit(SDL_INIT_VIDEO))
			{
				SDL_QuitSubSystem(SDL_INIT_VIDEO);
			}

			if(SDL_WasInit(SDL_INIT_EVENTS))
			{
				SDL_QuitSubSystem(SDL_INIT_EVENTS);
			}

			mIsInstalled = false;

			return true;
		}

		AE::OS::Window* WindowManagerSdl::createWindow(const std::string &windowTitle, AE::OS::WindowDesc &windowDesc)
		{
			AE::OS::Window *window = new AE::OS::WindowSdl(windowTitle, windowDesc);
			mWindows.push_back(window);

			/*AE::Graphics::Device::ContextDesc contextDesc;
			contextDesc.dimensions = window->getDimensions();
			contextDesc.fullScreen = windowDesc.fullScreen;
			contextDesc.parentWindow = window;
			contextDesc.setColorFormat(windowDesc.getColorFormat());*/

			return window;
		}

		AE::OS::Window* WindowManagerSdl::createWindow(const std::string &windowTitle, AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Context *deviceContext)
		{
			AE::OS::Window *window = createWindow(windowTitle, windowDesc);

			window->attachDeviceContext(deviceContext);

			return window;
		}

		void WindowManagerSdl::destroyWindow(AE::OS::Window *window)
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				if(*i == window)
					delete window;
			}
		}
	}
}