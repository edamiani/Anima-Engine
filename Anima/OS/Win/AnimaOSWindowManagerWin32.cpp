#include "../include/AnimaOSWindowManagerWin32.h"
#include "../include/AnimaOSWindowWin32.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowManagerWin32::WindowManagerWin32() 
		{
		}

		WindowManagerWin32::~WindowManagerWin32()
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
				delete *i;
		}

		AE::OS::Window* WindowManagerWin32::createWindow(const std::string &windowTitle, const AE::Math::Point2 &dimensions)
		{
			AE::OS::Window *window = new AE::OS::WindowWin32(windowTitle, AE::Math::Point2(dimensions.x, dimensions.y));
			mWindows.push_back(window);

			return window;
		}

		void WindowManagerWin32::destroyWindow(AE::OS::Window *window)
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