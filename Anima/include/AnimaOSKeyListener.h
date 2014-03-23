#ifndef __AE_OS_KEY_LISTENER__
#define __AE_OS_KEY_LISTENER__

#include "AnimaOSEvent.h"
#include "AnimaInputKeyInfo.h"

namespace AE
{
	namespace OS
	{
		struct Event;

		class KeyListener
		{
		public:
			KeyListener() {}
			virtual ~KeyListener() 
			{
			}

			// Keyboard events
			virtual void onKeyDown(const AE::OS::EventKeyboard &event) { }
			virtual void onKeyTranslation(const AE::OS::EventKeyTranslation &event) { }
			virtual void onKeyUp(const AE::OS::EventKeyboard &event) { }
		};
	}
}

#endif