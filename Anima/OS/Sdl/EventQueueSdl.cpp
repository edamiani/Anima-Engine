//#include "../include/AnimaOSProcessManagerWin32.h"
//#include "../include/AnimaOSProcessWin32.h"
#include "EventQueueSdl.h"
#include "WindowSdl.h"
#include "WindowManagerSdl.h"

//#include "AnimaGraphicsManager.h"
#include "Anima/Input/AnimaInputKeyInfo.h"
#include "Anima/OS/AnimaOSEvent.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		EventQueueSdl::EventQueueSdl()
		{
		}

		EventQueueSdl::~EventQueueSdl()
		{
			mWindowListeners.clear();
		}

		bool EventQueueSdl::getNextEvent(AE::OS::Event *eventContainer)
		{
			SDL_Event event;

			if(SDL_PollEvent(&event))
			{
				onEvent(&event);

				return true;
			}
			else
			{
				return false;
			}
		}

		bool EventQueueSdl::peekNextEvent()
		{
			return true;
		}

		void EventQueueSdl::registerWindowListener(AE::OS::WindowListener *windowListener)
		{
			mWindowListeners.push_back(windowListener);
		}

		bool EventQueueSdl::waitNextEvent()
		{
			SDL_Event event;

			if(SDL_WaitEvent(&event))
			{
				onEvent(&event);

				return true;
			}
			else
			{
				return false;
			}
		}

		void EventQueueSdl::onEvent(SDL_Event *event)
		{
			if(event->type == SDL_WINDOWEVENT) 
			{
				SDL_Window *sdlWindow = SDL_GetWindowFromID(event->window.windowID);
				AE::OS::WindowSdl *window = reinterpret_cast<AE::OS::WindowSdl *>(SDL_GetWindowData(sdlWindow, "AnimaWindow"));

				switch(event->window.event)
				{
					/*case WM_CHAR:
					{
						std::list<AE::OS::KeyListener *>::iterator i;
						for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
						{
							wchar_t character = (wchar_t)wParam;

							AE::OS::EventKeyTranslation keyEvent(window, character);
							(*i)->onKeyTranslation(keyEvent);
						}
						break;
					}*/

					case SDL_WINDOWEVENT_CLOSE:
					{
						std::list<AE::OS::WindowListener *>::iterator i;
						for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
							(*i)->onClose(window);
						break;
					}

					//case WM_DESTROY:
					//	::PostQuitMessage(0);
					//	break;

					//case WM_DISPLAYCHANGE:
					//	//if(window) window->onDisplayChange();
					//	break;

					//case WM_KEYDOWN:
					//{
					//	std::list<AE::OS::KeyListener *>::iterator i;
					//	for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
					//	{
					//		AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue)wParam);
					//		AE::OS::EventKeyboard keyEvent(AE::OS::EST_KEY_DOWN, window, keyInfo);
					//		(*i)->onKeyDown(keyEvent);
					//	}
					//	break;
					//}

					//case WM_PAINT:
					//	if(window) window->render();
					//	break;

					//case WM_SIZE:
					//	//if(window) window->onResize();
					//	break;

					//case WM_MOUSEMOVE:
					//{
					//	// TODO Fix the parameters!!!
					//	AE::OS::EventMouse mouseEvent(AE::OS::EST_MOUSE_AXES, window, 0, AE::Math::Point2<AE::int32>(0, 0));
					//	std::list<AE::OS::MouseListener *>::iterator i;
					//	for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
					//		(*i)->onMouseMove(mouseEvent);
					//	break;
					//}

					//case WM_LBUTTONUP:
					//	break;

					//case WM_SETFOCUS:
					//{
					//	std::list<AE::OS::WindowListener *>::iterator i;
					//	for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
					//		(*i)->onGainFocus(window);
					//	break;
					//}

					//case WM_KILLFOCUS:
					//{
					//	std::list<AE::OS::WindowListener *>::iterator i;
					//	for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
					//		(*i)->onLostFocus(window);
					//	break;
					//}

					//case WM_SHOWWINDOW:
					//{
					//	if(wParam == TRUE) // Window shown
					//	{
					//		WINDOWINFO windowInfo;
					//		windowInfo.cbSize = sizeof(WINDOWINFO);
					//		GetWindowInfo(hWnd, &windowInfo);

					//		AE::Math::Point2<AE::int32> topLeft = AE::Math::Point2<AE::int32>(windowInfo.rcWindow.left, windowInfo.rcWindow.top);
					//		AE::Math::Point2<AE::uint> dimensions = AE::Math::Point2<AE::uint>(windowInfo.rcWindow.right - windowInfo.rcWindow.left, windowInfo.rcWindow.bottom - windowInfo.rcWindow.top);
					//		std::list<AE::OS::WindowListener *>::iterator i;
					//		for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
					//			(*i)->onRestore(window, topLeft, dimensions);
					//	}
					//	else // Window hidden
					//	{
					//	}
					//	break;
					//}
				}
			}
		}
	}
}