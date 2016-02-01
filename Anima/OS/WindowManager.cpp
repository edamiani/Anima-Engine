#include "Anima/OS/WindowManager.h"

AE::OS::WindowManager* AE::OS::WindowManager::mInstance = 0;

namespace AE
{
	namespace OS
	{
		WindowManager::~WindowManager()
		{
			mWindows.clear();
		}
	}
}
