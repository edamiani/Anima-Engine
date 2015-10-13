#include "../include/AnimaOSProcessManagerLinux.h"
#include "../include/AnimaOSProcessLinux.h"
#include "../include/AnimaOSEventManagerLinux.h"
#include "../include/AnimaOSWindowLinux.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaInputKeyInfo.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		std::list<AE::OS::KeyListener *> EventManagerLinux::mKeyListeners;
		std::list<AE::OS::MouseListener *> EventManagerLinux::mMouseListeners;

		EventManagerLinux::EventManagerLinux()
		{
			AE::OS::EventManager::mInstance = this;
		}

		EventManagerLinux::~EventManagerLinux()
		{
			mKeyListeners.clear();
			mMouseListeners.clear();
			AE::OS::EventManager::mInstance = 0;
		}

		void EventManagerLinux::registerKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.push_back(keyListener);
		}

		void EventManagerLinux::registerMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.push_back(mouseListener);
		}

		void EventManagerLinux::unregisterKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.remove(keyListener);
		}

		void EventManagerLinux::unregisterMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.remove(mouseListener);
		}

//		LRESULT WINAPI EventManagerLinux::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//		{
//			AE::OS::WindowLinux *window = reinterpret_cast<AE::OS::WindowLinux *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
//			switch( msg )
//			{
//					case WM_DESTROY:
//						::PostQuitMessage(0);
//						break;
//					case WM_CLOSE:
//						if(window) window->onClose();
//						break;
//					case WM_DISPLAYCHANGE:
//						if(window) window->onDisplayChange();
//						break;
//					case WM_KEYDOWN:
//						{
//							std::list<AE::OS::KeyListener *>::iterator i;
//							for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
//							{
//								AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue)wParam);
//								(*i)->onKeyDown(AE::Input::KeyInfo(keyInfo));
//							}
//						}
//						break;
//					case WM_KEYUP:
//						{
//							std::list<AE::OS::KeyListener *>::iterator i;
//							for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
//							{
//								AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue)wParam);
//								(*i)->onKeyUp(AE::Input::KeyInfo(keyInfo));
//							}
//						}
//						break;
//					case WM_PAINT:
//						if(window) window->render();
//						break;
//					case WM_SIZE:
//						if(window) window->onResize();
//						break;
//					case WM_MOUSEMOVE:
//						{
//							std::list<AE::OS::MouseListener *>::iterator i;
//							for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
//								(*i)->onMouseMove();
//							break;
//						}
//					case WM_LBUTTONUP:
//						break;
//			}
//			return ::DefWindowProc( hWnd, msg, wParam, lParam );
//		}
	}
}
