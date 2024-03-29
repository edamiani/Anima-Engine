#include "Anima/OS/Win/WindowManagerWin.h"

#include "Anima/OS/Win/EventQueueWin.h"
#include "Anima/OS/Win/WindowWin.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{

	}

	namespace OS
	{
		WindowManagerWin::WindowManagerWin() 
		{
			mInstance = this;
		}

		WindowManagerWin::~WindowManagerWin()
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				delete *i;
			}

			mInstance = 0;
		}

		bool WindowManagerWin::install(AE::uint options)
		{
			if(mParent != 0)
			{
				mEventQueue = new AE::OS::EventQueueWin();

				mIsInstalled = true;

				return true;
			}
			else
				return false;
		}

		bool WindowManagerWin::uninstall()
		{
			delete mEventQueue;
			mEventQueue = 0;

			mIsInstalled = false;

			return true;
		}

		AE::OS::Window* WindowManagerWin::createWindow(const std::string &windowTitle, AE::OS::WindowDesc &windowDesc)
		{
			AE::OS::Window *window = new AE::OS::WindowWin(windowTitle, windowDesc);
			mWindows.push_back(window);

			/*AE::Graphics::Device::ContextDesc contextDesc;
			contextDesc.dimensions = window->getDimensions();
			contextDesc.fullScreen = windowDesc.fullScreen;
			contextDesc.parentWindow = window;
			contextDesc.setColorFormat(windowDesc.getColorFormat());*/

			return window;
		}

		AE::OS::Window* WindowManagerWin::createWindow(const std::string &windowTitle, AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Context *deviceContext)
		{
			AE::OS::Window *window = createWindow(windowTitle, windowDesc);

			window->attachDeviceContext(deviceContext);

			return window;
		}

		void WindowManagerWin::destroyWindow(AE::OS::Window *window)
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