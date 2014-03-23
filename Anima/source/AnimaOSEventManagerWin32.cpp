#include "../include/AnimaOSProcessManagerWin32.h"
#include "../include/AnimaOSProcessWin32.h"
#include "../include/AnimaOSEventManagerWin32.h"
#include "../include/AnimaOSWindowWin32.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaInputKeyInfo.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		std::list<AE::OS::KeyListener *> EventManagerWin32::mKeyListeners;
		std::list<AE::OS::MouseListener *> EventManagerWin32::mMouseListeners;

		EventManagerWin32::EventManagerWin32() 
		{
			AE::OS::EventManager::mInstance = this;
		}

		EventManagerWin32::~EventManagerWin32()
		{
			mKeyListeners.clear();
			mMouseListeners.clear();
			AE::OS::EventManager::mInstance = 0;
		}

		void EventManagerWin32::registerKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.push_back(keyListener);
		}
		
		void EventManagerWin32::registerMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.push_back(mouseListener);
		}

		void EventManagerWin32::unregisterKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.remove(keyListener);
		}
		
		void EventManagerWin32::unregisterMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.remove(mouseListener);
		}

		LRESULT WINAPI EventManagerWin32::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
		{
			AE::OS::WindowWin32 *window = reinterpret_cast<AE::OS::WindowWin32 *>(::GetWindowLongPtr(hWnd, GWLP_USERDATA));
			switch( msg )
			{
					case WM_DESTROY:
						::PostQuitMessage(0);
						break;
					case WM_CLOSE:
						if(window) window->onClose();
						break;
					case WM_DISPLAYCHANGE:
						if(window) window->onDisplayChange();
						break;
					case WM_KEYDOWN:
						{
							std::list<AE::OS::KeyListener *>::iterator i;
							for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
							{
								AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue)wParam);
								(*i)->onKeyDown(AE::Input::KeyInfo(keyInfo));
							}
						}
						break;
					case WM_KEYUP:
						{
							std::list<AE::OS::KeyListener *>::iterator i;
							for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
							{
								AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue)wParam);
								(*i)->onKeyUp(AE::Input::KeyInfo(keyInfo));
							}
						}
						break;
					case WM_PAINT:
						if(window) window->render();
						break;
					case WM_SIZE:
						if(window) window->onResize();
						break;
					case WM_MOUSEMOVE:
						{
							std::list<AE::OS::MouseListener *>::iterator i;
							for(i = mMouseListeners.begin(); i != mMouseListeners.end(); i++)
								(*i)->onMouseMove();
							break;
						}
					case WM_LBUTTONUP:
						break;
			}
			return ::DefWindowProc( hWnd, msg, wParam, lParam );
		}
	}
}