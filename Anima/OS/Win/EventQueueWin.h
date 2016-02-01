#ifndef __AE_OS_EVENT_QUEUE_WIN__
#define __AE_OS_EVENT_QUEUE_WIN__

#include "Anima/OS/EventQueue.h"
#include "Anima/Platform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class EventQueueWin : public AE::OS::EventQueue
		{
		public:
			EventQueueWin();
			virtual ~EventQueueWin();

			bool getNextEvent(AE::OS::Event *eventContainer);
			bool peekNextEvent();
			void registerWindowListener(AE::OS::WindowListener *windowListener);
			bool waitNextEvent();

			static LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		private:
			//void _dispatchEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			AE::OS::Event* _translateEvent(UINT msg);
		};
	}
}

#endif