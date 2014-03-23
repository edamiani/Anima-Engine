#ifndef __AE_OS_CONFIG__
#define __AE_OS_CONFIG__

#include "AnimaOSDeviceManager.h"
#include "AnimaOSEnums.h"
#include "AnimaOSEventQueue.h"
#include "AnimaOSWindowManager.h"
#include "AnimaPlatform.h"
#include "AnimaTypes.h"

namespace AE
{
	namespace OS
	{
		class Config
		{
		public:
			Config(AE::uint options);
			~Config();

		protected:
			AE::uint mOptions;
		};
	}
}

#endif