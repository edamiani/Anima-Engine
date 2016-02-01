#ifndef __AE_OS_MANAGER__
#define __AE_OS_MANAGER__

#include "Anima/OS/KeyListener.h"
#include "Anima/OS/MouseListener.h"

namespace AE
{
	namespace OS
	{
		class Manager
		{
		public:
			Manager() {}
			virtual ~Manager() {}

			virtual void quit() = 0;
			virtual void registerKeyListener(AE::OS::KeyListener *keyListener) = 0;
			virtual void registerMouseListener(AE::OS::MouseListener *mouseListener) = 0;
			virtual void unregisterKeyListener(AE::OS::KeyListener *keyListener) = 0;
			virtual void unregisterMouseListener(AE::OS::MouseListener *mouseListener) = 0;

			virtual void yield() = 0;
		};
	}
}

#endif