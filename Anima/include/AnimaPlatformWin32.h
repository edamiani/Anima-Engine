#ifndef __AE_PLATFORM_WIN32__
#define __AE_PLATFORM_WIN32__

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <oleauto.h>

#undef min
#undef max

#if defined( __MINGW32__ )
	#include <unistd.h>
#endif

#endif