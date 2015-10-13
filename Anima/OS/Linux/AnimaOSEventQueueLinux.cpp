//#include "../include/AnimaOSProcessManagerLinux.h"
//#include "../include/AnimaOSProcessLinux.h"
#include "../include/AnimaOSEvent.h"
#include "../include/AnimaOSEventQueueLinux.h"
#include "../include/AnimaOSWindowLinux.h"
#include "../include/AnimaOSWindowManagerLinux.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaInputKeyInfo.h"
#include <cassert>

namespace AE
{
    namespace OS
    {
        EventQueueLinux::EventQueueLinux()
        {
            mX11Display = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance())->_getX11Display();
        }

        EventQueueLinux::~EventQueueLinux()
        {
            mX11Display = 0;
        }

        bool EventQueueLinux::getNextEvent(AE::OS::Event *eventContainer)
        {
            XEvent x11Event;

            if(XEventsQueued(mX11Display, QueuedAfterFlush) > 0)
            {
                XNextEvent(mX11Display, &x11Event);

                return eventProc(x11Event);
            }

            return true;
        }

        bool EventQueueLinux::peekNextEvent()
        {
            XEvent x11Event;

            if(XEventsQueued(mX11Display, QueuedAlready) > 0)
            {
                XPeekEvent(mX11Display, &x11Event);

                return eventProc(x11Event);
            }

            return true;
        }

        void EventQueueLinux::registerWindowListener(AE::OS::WindowListener *windowListener)
        {
            mWindowListeners.push_back(windowListener);
        }

        bool EventQueueLinux::waitNextEvent()
        {
            XEvent x11Event;

            XNextEvent(mX11Display, &x11Event);

            return eventProc(x11Event);
        }

        bool EventQueueLinux::eventProc(XEvent event)
        {
            AE::OS::Event *translatedEvent = 0;

            switch(event.type)
            {
                case CreateNotify:
                {
//                    std::cout << "onCreate()" << std::endl;

//                    return true;
                    break;
                }
                case ClientMessage:
                {
                    AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
                    ::Display *x11display = myWindowManager->_getX11Display();

                    if( event.xclient.data.l[0] == XInternAtom(x11display, "WM_DELETE_WINDOW", false) )
                    {
//                        std::cout << "onDestroy()" << std::endl;

                        AE::OS::Window *window = myWindowManager->_getAEWindow(event.xclient.window);
                        if ( !window ) break;

                        translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_CLOSE, window);

                        std::list<AE::OS::WindowListener *>::iterator i;
                        for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
                            (*i)->onClose( window );

                        window->close();

//                        return false;
                        break;
                    }
                }
                case ResizeRequest:
                {
//                    std::cout << "onResize()" << std::endl;

                    AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
                    AE::OS::Window *window = myWindowManager->_getAEWindow(event.xresizerequest.window);

					if ( !window ) break;

                    AE::Math::Point2 topLeft = window->getPosition();
                    AE::Math::Point2 dimensions = AE::Math::Point2( event.xresizerequest.width, event.xresizerequest.height );

                    translatedEvent = new AE::OS::EventWindow( AE::OS::EST_WINDOW_RESIZE,  window, &topLeft, &dimensions );

                    std::list<AE::OS::WindowListener *>::iterator i;
                    for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
                        (*i)->onResize( window, topLeft, dimensions );

                    return false;
                }
                case FocusIn:
                {
//                    std::cout << "onGainFocus()" << std::endl;

                    AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
                    AE::OS::Window *window = myWindowManager->_getAEWindow(event.xfocus.window);

					if ( !window ) break;

                    translatedEvent = new AE::OS::EventWindow( AE::OS::EST_WINDOW_GAIN_FOCUS,  window );

                    std::list<AE::OS::WindowListener *>::iterator i;
                    for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
                        (*i)->onGainFocus( window );

                    break;
                }
                case FocusOut:
                {
//                    std::cout << "onLostFocus()" << std::endl;

                    AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
                    AE::OS::Window *window = myWindowManager->_getAEWindow(event.xfocus.window);

					if ( !window ) break;

                    translatedEvent = new AE::OS::EventWindow( AE::OS::EST_WINDOW_LOST_FOCUS,  window );

                    std::list<AE::OS::WindowListener *>::iterator i;
                    for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
                        (*i)->onLostFocus( window );

                    break;
                }
                case EnterNotify:
                {
//                    std::cout << "onEnterWindow()" << std::endl;

//                    translatedEvent = new AE::OS::EventMouse( AE::OS::EST_MOUSE_ENTER_WINDOW );

//                        std::list<AE::OS::MouseListener *>::iterator i;
//                        for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
//                            (*i)->onEnterWindow();

                    break;
                }
                case LeaveNotify:
                {
//                    std::cout << "onLeaveWindow()" << std::endl;

//                    translatedEvent = new AE::OS::EventMouse( AE::OS::EST_MOUSE_LEAVE_WINDOW );

//                        std::list<AE::OS::MouseListener *>::iterator i;
//                        for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
//                            (*i)->onLeaveWindow();

                    break;
                }
                case Expose:
                {
//                    std::cout << "onRestore()" << std::endl;

                    AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
                    AE::OS::Window *window = myWindowManager->_getAEWindow(event.xexpose.window);

                    if ( !window ) break;

                    translatedEvent = new AE::OS::EventWindow( AE::OS::EST_WINDOW_RESTORE,  window );

                    std::list<AE::OS::WindowListener *>::iterator i;
                    for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
                        (*i)->onRestore( window, AE::Math::Point2( event.xexpose.x, event.xexpose.y ), AE::Math::Point2( event.xexpose.width, event.xexpose.height ) );

                    window->render();

                    return true;
                }
                case KeyRelease:
                {
//                    std::cout << "onKeyUp()" << std::endl;
					AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
                    AE::OS::Window *window = myWindowManager->_getAEWindow(event.xkey.window);

                    if ( !window ) break;

                    AE::OS::EventKeyboard keyEvent( AE::OS::EST_KEY_UP, window, AE::Input::KeyInfo((AE::Input::KeyValue) event.xkey.keycode) );

                    std::list<AE::OS::KeyListener *>::iterator i;
                    for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
                        (*i)->onKeyUp( keyEvent );

                    break;
                }
                case KeyPress:
                {
//                    std::cout << "onKeyDown()" << std::endl;

					AE::OS::WindowManagerLinux *myWindowManager = static_cast<AE::OS::WindowManagerLinux *>(AE::OS::WindowManager::getInstance());
                    AE::OS::Window *window = myWindowManager->_getAEWindow(event.xkey.window);

                    if ( !window ) break;

                    AE::OS::EventKeyboard keyEvent( AE::OS::EST_KEY_UP, window, AE::Input::KeyInfo((AE::Input::KeyValue) event.xkey.keycode) );
                    AE::OS::EventKeyTranslation keyTranslation( window, L'M' ); // TODO figure a good way to translate the keycode to unicode - Nivaldo

                    std::list<AE::OS::KeyListener *>::iterator i;
                    AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue) event.xkey.keycode);
                    for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
                    {
                    	(*i)->onKeyDown( keyEvent );
                        (*i)->onKeyTranslation( keyTranslation );
                    }

                    break;
                }
                case MotionNotify:
                {
//                    std::cout << "onMouseMove()" << std::endl;

                    std::list<AE::OS::MouseListener *>::iterator i;

//                    translatedEvent = new AE::OS::EventMouse( AE::OS::EST_MOUSE_AXES ); // ???

                    for (i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
                        (*i)->onMouseMove();

                    return true;
                }
                case ButtonRelease:
                {
//                    std::cout << "onButtonUp()" << std::endl;

//                    translatedEvent = new AE::OS::EventMouse( AE::OS::EST_MOUSE_BUTTON_UP );

                    std::list<AE::OS::MouseListener *>::iterator i;
                    for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
                        (*i)->onButtonUp();

                    break;
                }
                case ButtonPress:
                {
//                    std::cout << "onButtonDown()" << std::endl;

//                    translatedEvent = new AE::OS::EventMouse( AE::OS::EST_MOUSE_BUTTON_DOWN );

                    std::list<AE::OS::MouseListener *>::iterator i;
                    for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
                        (*i)->onButtonDown();

                    break;
                }
                case DestroyNotify:
                {
//                    std::cout << "DestroyNotify" << std::endl;
                }
                default:
                {
//                    std::cout << "..." << std::endl;
                }
            }
            return true;
        }
    }
}


