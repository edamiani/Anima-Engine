//#include "../include/AnimaOSProcessManagerWin32.h"
//#include "../include/AnimaOSProcessWin32.h"
#include "AnimaOSEventQueueWin.h"
#include "AnimaOSWindowWin.h"
#include "AnimaOSWindowManagerWin.h"

//#include "AnimaGraphicsManager.h"
#include "Anima/Input/AnimaInputKeyInfo.h"
#include "Anima/OS/AnimaOSEvent.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		EventQueueWin::EventQueueWin() 
		{
		}

		EventQueueWin::~EventQueueWin()
		{
			mWindowListeners.clear();
		}

		bool EventQueueWin::getNextEvent(AE::OS::Event *eventContainer)
		{
			MSG message;
			::PeekMessage(&message, NULL, NULL, NULL, PM_REMOVE);
			if(message.message != WM_QUIT)
			{
				::TranslateMessage(&message);
				::DispatchMessage(&message);
				return true;
			}
			else
				return false;
		}

		bool EventQueueWin::peekNextEvent()
		{
			/*MSG message;
			::PeekMessage(&message, NULL, NULL, NULL, PM_NOREMOVE);
			if(message.message != WM_QUIT)
			{
				::TranslateMessage(&message);
				::DispatchMessage(&message);
				return true;
			}
			else
				return false;*/
			return true;
		}

		void EventQueueWin::registerWindowListener(AE::OS::WindowListener *windowListener)
		{
			mWindowListeners.push_back(windowListener);
		}

		bool EventQueueWin::waitNextEvent()
		{
			MSG message;
			BOOL result = ::GetMessage(&message, NULL, NULL, NULL);

			if(result > 0)
			{
				::TranslateMessage(&message);
				::DispatchMessage(&message);
				return true;
			}
			else
			{
				//DWORD error = ::GetLastError();
				return false;
			}
		}

		LRESULT WINAPI EventQueueWin::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			AE::OS::WindowWin *window = reinterpret_cast<AE::OS::WindowWin *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
			switch(msg)
			{
				case WM_CHAR:
				{
					std::list<AE::OS::KeyListener *>::iterator i;
					for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
					{
						wchar_t character = (wchar_t)wParam;

						AE::OS::EventKeyTranslation keyEvent(window, character);
						(*i)->onKeyTranslation(keyEvent);
					}
					break;
				}

				case WM_CLOSE:
				{
					std::list<AE::OS::WindowListener *>::iterator i;
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onClose(window);
					break;
				}

				case WM_DESTROY:
					::PostQuitMessage(0);
					break;

				case WM_DISPLAYCHANGE:
					//if(window) window->onDisplayChange();
					break;

				case WM_KEYDOWN:
				{
					std::list<AE::OS::KeyListener *>::iterator i;
					for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
					{
						AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue)wParam);
						AE::OS::EventKeyboard keyEvent(AE::OS::EST_KEY_DOWN, window, keyInfo);
						(*i)->onKeyDown(keyEvent);
					}
					break;
				}

				case WM_PAINT:
					if(window) window->render();
					break;

				case WM_SIZE:
					//if(window) window->onResize();
					break;

				case WM_MOUSEMOVE:
				{
					// TODO Fix the parameters!!!
					AE::OS::EventMouse mouseEvent(AE::OS::EST_MOUSE_AXES, window, 0, AE::Math::Point2<AE::int32>(0, 0));
					std::list<AE::OS::MouseListener *>::iterator i;
					for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
						(*i)->onMouseMove(mouseEvent);
					break;
				}

				case WM_LBUTTONUP:
					break;

				case WM_SETFOCUS:
				{
					std::list<AE::OS::WindowListener *>::iterator i;
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onGainFocus(window);
					break;
				}

				case WM_KILLFOCUS:
				{
					std::list<AE::OS::WindowListener *>::iterator i;
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onLostFocus(window);
					break;
				}

				case WM_SHOWWINDOW:
				{
					if(wParam == TRUE) // Window shown
					{
						WINDOWINFO windowInfo;
						windowInfo.cbSize = sizeof(WINDOWINFO);
						GetWindowInfo(hWnd, &windowInfo);

						AE::Math::Point2<AE::int32> topLeft = AE::Math::Point2<AE::int32>(windowInfo.rcWindow.left, windowInfo.rcWindow.top);
						AE::Math::Point2<AE::uint> dimensions = AE::Math::Point2<AE::uint>(windowInfo.rcWindow.right - windowInfo.rcWindow.left, windowInfo.rcWindow.bottom - windowInfo.rcWindow.top);
						std::list<AE::OS::WindowListener *>::iterator i;
						for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
							(*i)->onRestore(window, topLeft, dimensions);
					}
					else // Window hidden
					{
					}
					break;
				}
			}

			return ::DefWindowProc( hWnd, msg, wParam, lParam );

			/*if(allegroEvent->type > ALLEGRO_EVENT_DISPLAY_EXPOSE)
			{
				AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(allegroEvent->display.source);
				std::list<AE::OS::WindowListener *>::iterator i;

				switch(allegroEvent->type)
				{
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onClose(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_EXPOSE:
					{
						AE::Math::Point2 topLeft = AE::Math::Point2(allegroEvent->display.x, allegroEvent->display.y);
						AE::Math::Point2 dimensions = AE::Math::Point2(allegroEvent->display.width, allegroEvent->display.height);
						for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
							(*i)->onRestore(window, topLeft, dimensions);
						break;
					}

				case ALLEGRO_EVENT_DISPLAY_FOUND:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onDeviceFound(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_LOST:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onDeviceLost(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onOrientationChanged(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_RESIZE:
					{
						AE::Math::Point2 topLeft = AE::Math::Point2(allegroEvent->display.x, allegroEvent->display.y);
						AE::Math::Point2 dimensions = AE::Math::Point2(allegroEvent->display.width, allegroEvent->display.height);
						for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
							(*i)->onResize(window, topLeft, dimensions);
						break;
					}

				case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onGainFocus(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onLostFocus(window);
					break;
				}
			}*/
		}

		AE::OS::Event* EventQueueWin::_translateEvent(UINT msg)
		{
			AE::OS::Event *translatedEvent = 0;

			/*switch(event->type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_CLOSE, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_EXPOSE:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					AE::Math::Point2 topLeft = AE::Math::Point2(event->display.x, event->display.y);
					AE::Math::Point2 dimensions = AE::Math::Point2(event->display.width, event->display.height);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_RESTORE, window, &topLeft, &dimensions);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_FOUND:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_DEVICE_FOUND, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_LOST:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_DEVICE_LOST, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_ORIENTATION_CHANGED, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					AE::Math::Point2 topLeft = AE::Math::Point2(event->display.x, event->display.y);
					AE::Math::Point2 dimensions = AE::Math::Point2(event->display.width, event->display.height);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_RESIZE, window, &topLeft, &dimensions);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_GAIN_FOCUS, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_LOST_FOCUS, window);
					break;
				}

			case ALLEGRO_EVENT_JOYSTICK_AXIS:
				break;

			case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
				break;

			case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
				break;

			case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
				break;

			case ALLEGRO_EVENT_KEY_CHAR:
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				break;

			case ALLEGRO_EVENT_KEY_UP:
				break;

			case ALLEGRO_EVENT_MOUSE_AXES:
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				break;

			case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
				break;

			case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
				break;

			case ALLEGRO_EVENT_MOUSE_WARPED:
				break;
			}

			return translatedEvent;*/
			return translatedEvent;
		}
	}
}