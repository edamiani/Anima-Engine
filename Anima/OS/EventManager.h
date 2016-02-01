#ifndef __AE_OS_EVENT_MANAGER__
#define __AE_OS_EVENT_MANAGER__

#include "Anima/OS/KeyListener.h"
#include "Anima/OS/MouseListener.h"
#include "Anima/OS/WindowMetrics.h"
#include "Anima/Platform.h"

#include <list>

namespace AE
{
	namespace OS
	{
		class EventManager
		{
		public:
			EventManager() {}
			virtual ~EventManager() {}

			virtual void registerKeyListener(AE::OS::KeyListener *keyListener);
			virtual void registerMouseListener(AE::OS::MouseListener *mouseListener);
			virtual void unregisterKeyListener(AE::OS::KeyListener *keyListener);
			virtual void unregisterMouseListener(AE::OS::MouseListener *mouseListener);

		protected:
			AE::OS::WindowMetrics mWindowMetrics;
		};
	}
}

#endif