#include "../include/AnimaOSWindowManagerOSX.h"
#include "../include/AnimaOSWindowOSX.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowManagerOSX::WindowManagerOSX() 
		{
		}

		WindowManagerOSX::~WindowManagerOSX()
		{
/*			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
				delete *i;
*/		}

		AE::OS::Window* WindowManagerOSX::createWindow(const std::string &windowTitle, const AE::Math::Point2 &dimensions)
		{
/*			AE::OS::Window *window = new AE::OS::WindowOSX(windowTitle, AE::Math::Point2(dimensions.x, dimensions.y));
			mWindows.push_back(window);

			return window;
 */		return 0;
		}

		void WindowManagerOSX::destroyWindow(AE::OS::Window *window)
		{
		/*	std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				if(*i == window)
					delete window;
			} */
		}
	}
}