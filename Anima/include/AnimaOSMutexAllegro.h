#ifndef __AE_OS_MUTEX_ALLEGRO__
#define __AE_OS_MUTEX_ALLEGRO__

#include "AnimaOSMutex.h"
#include "AnimaTypes.h"

#include "allegro5/allegro.h"

namespace AE
{
	namespace OS
	{
		class MutexAllegro : public AE::OS::Mutex
		{
		public:
			MutexAllegro(bool allowsRecursiveLock = false) 
			{
				if(allowsRecursiveLock)
					mAllegroMutex = al_create_mutex_recursive();
				else
					mAllegroMutex = al_create_mutex();
			}

			virtual ~MutexAllegro() {}

		protected:
			ALLEGRO_MUTEX *mAllegroMutex;
		}
	}
}

#endif