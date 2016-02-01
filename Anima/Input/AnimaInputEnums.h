#ifndef __AE_INPUT_ENUMS__
#define __AE_INPUT_ENUMS__

#include "Anima/Platform.h"

//#ifdef AE_PLATFORM_ALLEGRO
//#	include "AnimaInputKeyValueAllegro.h"
//#else
#	ifdef AE_PLATFORM_WIN32
#		include "Anima/Input/Win32/AnimaInputKeyValueWin32.h"
#	elif defined(AE_PLATFORM_OSX)
#		include "Anima/Input/AnimaInputKeyValueOSX.h"
#	elif defined(AE_PLATFORM_LINUX)
#		include "Anima/Input/AnimaInputKeyValueLinux.h"
#	endif
//#endif

namespace AE
{
	namespace Input
	{
		enum MouseButtonType
		{
			MBT_LEFT = 0,
			MBT_RIGHT,
			MBT_MIDDLE,
			MBT_BUTTON3,
			MBT_BUTTON4,
			MBT_BUTTON5,
			MBT_BUTTON6,
			MBT_BUTTON7
		};
	}
}

#endif
