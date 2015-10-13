#ifndef __AE_OS_EVENT_MANAGER_OGRE__
#define __AE_OS_EVENT_MANAGER_OGRE__

#include "AnimaOSEventManager.h"
#include "AnimaPlatform.h"

#include "Ogre.h"
#include "OgreWindowEventUtilities.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class EventManagerOgre : public AE::OS::EventManager, public Ogre::WindowEventListener
		{
		public:
			EventManagerOgre();
			virtual ~EventManagerOgre();

			bool getNextEvent(AE::OS::Event *eventContainer);
			bool peekNextEvent();
			void registerWindowListener(AE::OS::WindowListener *windowListener);
			void waitNextEvent();

			//ALLEGRO_EVENT_QUEUE* _getAllegroEventQueue() { return mAllegroEventQueue; }

		private:
			///=void _dispatchEvent(ALLEGRO_EVENT *allegroEvent);
			//AE::OS::Event* _translateEvent(ALLEGRO_EVENT *allegroEvent);

			//ALLEGRO_EVENT_QUEUE *mAllegroEventQueue;
			//ALLEGRO_EVENT mAllegroEvent;
		};
	}
}

#endif