#ifndef __AE_OS_THREAD_ALLEGRO__
#define __AE_OS_THREAD_ALLEGRO__

#include "AnimaOSThread.h"

#include "allegro5/allegro.h"

namespace AE
{
	namespace OS
	{
		class ThreadAllegro : public AE::OS::Thread
		{
		public:
			ThreadAllegro(AE::OS::AsyncElement *asyncElement) : Thread(asyncElement), mAsyncElement(asyncElement) 
			{
				mAllegroThread = al_create_thread(/* todo */);
			}

			virtual ~ThreadAllegro() 
			{
				al_destroy_thread(mAllegroThread);
			}

			void join(const AE::OS::Thread &otherThread, void **returnValue){}
			void start() {}

		protected:
			ALLEGRO_THREAD *mAllegroThread;
		}
	}
}

#endif