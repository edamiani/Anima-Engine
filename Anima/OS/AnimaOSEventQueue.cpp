#include "../include/AnimaOSEventQueue.h"
/*
#ifdef AE_PLATFORM_ALLEGRO
#	include "../include/AnimaOSEventManagerAllegro.h"
#else
#	if defined(AE_PLATFORM_WIN32)
#		include "../include/AnimaOSEventManagerWin32.h"
#	endif
#endif
*/

std::list<AE::OS::KeyListener *> AE::OS::EventQueue::mKeyListeners;
std::list<AE::OS::MouseListener *> AE::OS::EventQueue::mMouseListeners;
std::list<AE::OS::WindowListener *> AE::OS::EventQueue::mWindowListeners;

namespace AE
{
	namespace OS
	{
		/*AE::OS::EventManager* EventManager::initialize()
		{
#		ifdef AE_PLATFORM_ALLEGRO
			mInstance = new AE::OS::EventManagerAllegro();
#		else
#			if defined(AE_PLATFORM_WIN32)
				mInstance = new AE::OS::EventManagerWin32();
#			endif
#		endif
			return mInstance;
		}*/

		/*void EventManager::shutdown()
		{
			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}*/

		EventQueue::~EventQueue()
		{
			mKeyListeners.clear();
			mMouseListeners.clear();
			mWindowListeners.clear();
		}

		void EventQueue::registerKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.push_back(keyListener);
		}
		
		void EventQueue::registerMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.push_back(mouseListener);
		}

		void EventQueue::registerWindowListener(AE::OS::WindowListener *windowListener)
		{
			mWindowListeners.push_back(windowListener);
		}

		void EventQueue::unregisterKeyListener(AE::OS::KeyListener *keyListener)
		{
			mKeyListeners.remove(keyListener);
		}
		
		void EventQueue::unregisterMouseListener(AE::OS::MouseListener *mouseListener)
		{
			mMouseListeners.remove(mouseListener);
		}

		void EventQueue::unregisterWindowListener(AE::OS::WindowListener *windowListener)
		{
			mWindowListeners.remove(windowListener);
		}
	}
}