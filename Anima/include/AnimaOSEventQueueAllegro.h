#ifndef __AE_OS_EVENT_QUEUE_ALLEGRO__
#define __AE_OS_EVENT_QUEUE_ALLEGRO__

#include "AnimaOSEventQueue.h"
#include "AnimaPlatform.h"

#include "allegro5/allegro.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class EventQueueAllegro : public AE::OS::EventQueue
		{
		public:
			EventQueueAllegro();
			virtual ~EventQueueAllegro();

			bool getNextEvent(AE::OS::Event *eventContainer);
			bool peekNextEvent();
			void registerWindowListener(AE::OS::WindowListener *windowListener);
			bool waitNextEvent();

			ALLEGRO_EVENT_QUEUE* _getAllegroEventQueue() { return mAllegroEventQueue; }

		private:
			void _dispatchEvent(ALLEGRO_EVENT *allegroEvent);
			AE::OS::Event* _translateEvent(ALLEGRO_EVENT *allegroEvent);

			ALLEGRO_EVENT_QUEUE *mAllegroEventQueue;
			ALLEGRO_EVENT mAllegroEvent;
		};
	}
}

#endif