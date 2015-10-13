#include "../include/AnimaOSProcessManagerWin32.h"
#include "../include/AnimaOSEventManagerWin32.h"
#include "../include/AnimaOSProcessWin32.h"

namespace AE
{
	namespace OS
	{
		ProcessManagerWin32::ProcessManagerWin32()
		{
		}

		ProcessManagerWin32::~ProcessManagerWin32()
		{
		}

		AE::OS::Process* ProcessManagerWin32::createProcess()
		{
			return 0;
		}
	}
}