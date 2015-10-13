#include "../include/AnimaOSWindowLinux.h"

#include "../include/AnimaOSWindowManagerLinux.h"
#include <X11/Xlib.h>


namespace AE
{
	namespace OS
	{
		WindowLinux::WindowLinux(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc)
			: Window(windowTitle, windowDesc)
		{
		    AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
			::Display *x11display = myWindowManager->_getX11Display();

		    mScreenID = XDefaultScreen(x11display);

            XSetWindowAttributes attributes;
            Visual *visual = XDefaultVisual(x11display, mScreenID);

            attributes.background_pixel		= XWhitePixel(x11display, mScreenID);
            attributes.border_pixel			= XBlackPixel(x11display, mScreenID);
//            attributes.override_redirect	= True;
            attributes.override_redirect	= False;
            attributes.event_mask			= ButtonPressMask        |
                                              ButtonReleaseMask      |
                                              PointerMotionMask      |
                                              StructureNotifyMask    |
                                              SubstructureNotifyMask |
                                              ResizeRedirectMask     |
                                              KeyPressMask           |
                                              KeyReleaseMask         |
                                              ExposureMask           |
                                              EnterWindowMask        |
                                              LeaveWindowMask        |
//                                              VisibilityChangeMask   |
                                              FocusChangeMask;


		    mWindow = XCreateWindow(x11display,
                                    RootWindow(x11display, mScreenID),
                                    windowDesc.position.x, windowDesc.position.y,
                                    windowDesc.dimensions.x, windowDesc.dimensions.y,
                                    1, /* border width */
                                    CopyFromParent, /* color depth */
                                    InputOutput, /* window class */
                                    visual,
                                    CWBackPixel | CWBorderPixel | CWEventMask | CWOverrideRedirect /* enabled attributes */,
                                    &attributes);

            XStoreName(x11display, mWindow, windowTitle.c_str());

            // Override of the 'x' button (the closing one)
            Atom wmDeleteMessage = XInternAtom(x11display, "WM_DELETE_WINDOW", false);
            XSetWMProtocols(x11display, mWindow, &wmDeleteMessage, 1);
		}

		WindowLinux::~WindowLinux()
		{
        }

        void WindowLinux::close()
        {
            std::list<AE::OS::Window *> windowList = AE::OS::WindowManager::getInstance()->getWindowList();
            windowList.remove(this); // TODO what about this window children?

			delete mDeviceContext;

            AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
            ::Display *x11display = myWindowManager->_getX11Display();

            XDestroyWindow(x11display, mWindow);
        }

        void WindowLinux::show()
        {
            AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
            ::Display *x11display = myWindowManager->_getX11Display();

            XMapWindow( x11display, mWindow );

            myWindowManager->getEventQueue()->getNextEvent(0);
        }
	}
}
