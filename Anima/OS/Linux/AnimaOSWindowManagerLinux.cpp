#include "../include/AnimaOSWindowManagerLinux.h"

#include "../include/AnimaOSEventQueueLinux.h"
#include "../include/AnimaOSWindowLinux.h"

//#include <X11/Xlib.h>

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowManagerLinux::WindowManagerLinux()
		{
			mInstance = this;
		}

		WindowManagerLinux::~WindowManagerLinux()
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
				delete *i;

			mInstance = 0;
		}

		bool WindowManagerLinux::install(AE::uint options)
		{
			mX11Display = XOpenDisplay(NULL);

			mEventQueue = new AE::OS::EventQueueLinux();

			mIsInstalled = true;

			return true;
		}

		bool WindowManagerLinux::uninstall()
		{
			delete mEventQueue;
			mEventQueue = 0;

			XCloseDisplay(mX11Display);

			mIsInstalled = false;

			return true;
		}

		AE::OS::Window* WindowManagerLinux::createWindow(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Driver *deviceDriver)
		{
			AE::OS::Window *window = new AE::OS::WindowLinux(windowTitle, windowDesc);
			mWindows.push_back(window);

			return window;
		}

		void WindowManagerLinux::destroyWindow(AE::OS::Window *window)
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				if(*i == window)
					delete window;
			}
		}

		AE::OS::Window* AE::OS::WindowManagerLinux::_getAEWindow(::Window window)
		{
		    std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				if( static_cast<AE::OS::WindowLinux *>(*i)->_getX11Window() == window )
                    return (*i);
			}
            return 0;
		}
	}
}
