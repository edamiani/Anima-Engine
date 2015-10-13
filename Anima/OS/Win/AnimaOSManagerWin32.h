#ifndef __AE_OS_MANAGER_WIN32__
#define __AE_OS_MANAGER_WIN32__

#include "AnimaOSManager.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class ManagerWin32 : public AE::OS::Manager
		{
		public:
			ManagerWin32() {}
			virtual ~ManagerWin32();

			void quit() { ::PostQuitMessage(0); }
			void registerKeyListener(AE::OS::KeyListener *keyListener);
			void registerMouseListener(AE::OS::MouseListener *mouseListener);
			void unregisterKeyListener(AE::OS::KeyListener *keyListener);
			void unregisterMouseListener(AE::OS::MouseListener *mouseListener);
			void yield() { Sleep(0); }

			static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		private:
			static std::list<AE::OS::KeyListener *> mKeyListeners;
			static std::list<AE::OS::MouseListener *> mMouseListeners;
		};
	}
}

#endif