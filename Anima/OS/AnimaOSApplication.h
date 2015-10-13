#ifndef __AE_OS_APPLICATION__
#define __AE_OS_APPLICATION__

#include "AnimaOSWindow.h"
#include "../Graphics/AnimaGraphicsEnums.h"

#include <map>

namespace AE
{
	namespace OS
	{
		class Application
		{
		public:
			virtual ~Application() {}

			static AE::OS::Application*	getInstance() { assert(mInstance != 0); return mInstance; }

			virtual bool				dispatchNextMessage() = 0;
			static AE::OS::Application*	initialize(AE::Graphics::RenderType renderType);
			virtual void				quit() = 0;
			static void					shutdown();
			virtual bool				waitAndDispatchNextMessage() = 0;
			virtual void				yield() = 0;

		protected:
			Application() : mWindowCounter(0) {  }

			static AE::OS::Application*				mInstance;
			AE::uint8								mWindowCounter;
			std::map<AE::uint8, AE::OS::Window *>	mWindows;
		};
	}
}

#endif