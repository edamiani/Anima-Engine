#ifndef __AE_OS_PROCESS__
#define __AE_OS_PROCESS__

#include "AnimaOSWindow.h"
#include "AnimaGraphicsEnums.h"

#include <map>

namespace AE
{
	namespace OS
	{
		class Process
		{
		public:
			Process() {}
			virtual ~Process() {}

			virtual bool dispatchNextMessage() = 0;
			virtual void quit() = 0;
			virtual bool waitAndDispatchNextMessage() = 0;
			virtual void yield() = 0;

		protected:
			AE::uint16 mId;
		};
	}
}

#endif