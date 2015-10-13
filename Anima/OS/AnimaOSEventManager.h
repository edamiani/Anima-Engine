#ifndef __AE_OS_EVENT_MANAGER__
#define __AE_OS_EVENT_MANAGER__

#include "AnimaOSKeyListener.h"
#include "AnimaOSMouseListener.h"
#include "AnimaOSWindowMetrics.h"
#include "AnimaPlatform.h"

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