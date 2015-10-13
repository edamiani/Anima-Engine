#ifndef __AE_OS_EVENT_QUEUE_LINUX__
#define __AE_OS_EVENT_QUEUE_LINUX__

#include "AnimaOSEventQueue.h"
#include "AnimaPlatform.h"

#include <X11/keysym.h>
#include <X11/Xlib.h>

#include <list>

namespace AE
{
	namespace OS
	{
		class EventQueueLinux : public AE::OS::EventQueue
		{
		public:
			EventQueueLinux();
			virtual ~EventQueueLinux();

			bool getNextEvent(AE::OS::Event *eventContainer);
			bool peekNextEvent();
			void registerWindowListener(AE::OS::WindowListener *windowListener);
			bool waitNextEvent();

		protected:
			bool eventProc(::XEvent event);

			::Display *mX11Display;
		};
	}
}

#endif
