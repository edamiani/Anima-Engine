#ifndef __AE_OS_DEVICE__
#define __AE_OS_DEVICE__

#include "AnimaTypes.h"

namespace AE
{
	namespace OS
	{
		class Device
		{
		public:
			Device() {}
			virtual ~Device() {}

			virtual bool initialize(AE::uint options) = 0;
		};
	}
}

#endif