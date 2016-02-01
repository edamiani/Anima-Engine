#ifndef __AE_OS_KEY_TRANSLATION_LISTENER__
#define __AE_OS_KEY_TRANSLATION_LISTENER__

#include "Anima/OS/Event.h"

namespace AE
{
	namespace OS
	{
		struct Event;

		class KeyTranslationListener
		{
		public:
			KeyTranslationListener() {}
			virtual ~KeyTranslationListener() 
			{
			}

			// Translated character event
			virtual void onKeyTranslation(const AE::OS::EventCharacterTranslation &event) = 0;
		};
	}
}

#endif