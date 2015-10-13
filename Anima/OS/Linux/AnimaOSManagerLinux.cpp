#include "../include/AnimaOSManagerLinux.h"
#include "../include/AnimaOSWindowLinux.h"
#include "../include/AnimaGraphicsManager.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		std::list<AE::OS::KeyListener *> ManagerLinux::mKeyListeners;
		std::list<AE::OS::MouseListener *> ManagerLinux::mMouseListeners;

		ManagerLinux::~ManagerLinux()
		{
			mKeyListeners.clear();
			mMouseListeners.clear();
		}

		void ManagerLinux::registerKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.push_back(keyListener);
		}

		void ManagerLinux::registerMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.push_back(mouseListener);
		}

		void ManagerLinux::unregisterKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.remove(keyListener);
		}

		void ManagerLinux::unregisterMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.remove(mouseListener);
		}

//		LRESULT WINAPI ManagerLinux::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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
//						if(wParam == VK_ESCAPE)
//						{
//							if(window)
//								delete window;
//						}
//						else
//						{
//							std::list<AE::OS::KeyListener *>::iterator i;
//							for(i = mKeyListeners.begin(); i != mKeyListeners.end(); i++)
//							{
//								AE::Input::KeyInfo keyInfo = AE::Input::KeyInfo((AE::Input::KeyValue)wParam);
//								(*i)->onKeyDown(AE::Input::KeyInfo(keyInfo));
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