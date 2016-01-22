#ifndef __AE_OS_EVENT_QUEUE_WIN__
#define __AE_OS_EVENT_QUEUE_WIN__

#include "../AnimaOSEventQueue.h"
#include "Anima/AnimaPlatform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class EventQueueSdl : public AE::OS::EventQueue
		{
		public:
			EventQueueSdl();
			virtual ~EventQueueSdl();

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