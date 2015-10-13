#include "../include/AnimaOSProcessManagerOSX.h"
#include "../include/AnimaOSProcessOSX.h"
#include "../include/AnimaOSEventManagerOSX.h"
#include "../include/AnimaOSWindowOSX.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaInputKeyInfo.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		std::list<AE::OS::KeyListener *> EventManagerOSX::mKeyListeners;
		std::list<AE::OS::MouseListener *> EventManagerOSX::mMouseListeners;

		EventManagerOSX::EventManagerOSX() 
		{
//			AE::OS::EventManager::mInstance = this;
		}

		EventManagerOSX::~EventManagerOSX()
		{
/*			mKeyListeners.clear();
			mMouseListeners.clear();
			AE::OS::EventManager::mInstance = 0;
*/		}

		void EventManagerOSX::registerKeyListener(AE::OS::KeyListener *keyListener)
		{
//			mKeyListeners.push_back(keyListener);
		}
		
		void EventManagerOSX::registerMouseListener(AE::OS::MouseListener *mouseListener)
		{
//			mMouseListeners.push_back(mouseListener);
		}

		void EventManagerOSX::unregisterKeyListener(AE::OS::KeyListener *keyListener)
		{
//			mKeyListeners.remove(keyListener);
		}
		
		void EventManagerOSX::unregisterMouseListener(AE::OS::MouseListener *mouseListener)
		{
//			mMouseListeners.remove(mouseListener);
		}

	}
}