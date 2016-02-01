#ifndef __AE_OS_EVENT_QUEUE__
#define __AE_OS_EVENT_QUEUE__

#include "Anima/OS/KeyListener.h"
#include "Anima/OS/MouseListener.h"
#include "Anima/OS/WindowListener.h"

#include <cassert>
#include <list>

namespace AE
{
	namespace OS
	{
		struct Event;

		class EventQueue
		{
		public:
			EventQueue() {}
			virtual ~EventQueue();

			virtual bool getNextEvent(AE::OS::Event *eventContainer) = 0;
			virtual bool peekNextEvent() = 0;
			virtual void registerKeyListener(AE::OS::KeyListener *keyListener);
			virtual void registerMouseListener(AE::OS::MouseListener *mouseListener);
			virtual void registerWindowListener(AE::OS::WindowListener *windowListener);
			virtual void unregisterKeyListener(AE::OS::KeyListener *keyListener);
			virtual void unregisterMouseListener(AE::OS::MouseListener *mouseListener);
			virtual void unregisterWindowListener(AE::OS::WindowListener *windowListener);
			virtual bool waitNextEvent() = 0;

		protected:
			static std::list<AE::OS::KeyListener *>		mKeyListeners;
			static std::list<AE::OS::MouseListener *>	mMouseListeners;
			static std::list<AE::OS::WindowListener *>	mWindowListeners;
		};
	}
}

#endif
