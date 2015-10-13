#ifndef __AE_OS_EVENT_MANAGER_WIN32__
#define __AE_OS_EVENT_MANAGER_WIN32__

#include "AnimaOSEventManager.h"
#include "AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class EventManagerWin32 : public AE::OS::EventManager
		{
		public:
			EventManagerWin32();
			virtual ~EventManagerWin32();

			void registerKeyListener(AE::OS::KeyListener *keyListener);
			void registerMouseListener(AE::OS::MouseListener *mouseListener);
			void unregisterKeyListener(AE::OS::KeyListener *keyListener);
			void unregisterMouseListener(AE::OS::MouseListener *mouseListener);

			static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		private:
			static std::list<AE::OS::KeyListener *> mKeyListeners;
			static std::list<AE::OS::MouseListener *> mMouseListeners;
		};
	}
}

#endif