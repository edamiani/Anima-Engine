#ifndef __AE_OS_EVENT_QUEUE_WIN__
#define __AE_OS_EVENT_QUEUE_WIN__

#include "../AnimaOSEventQueue.h"
#include "Anima/AnimaPlatform.h"

#include "SDL.h"

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

		private:
			void onEvent(SDL_Event *event);
		};
	}
}

#endif