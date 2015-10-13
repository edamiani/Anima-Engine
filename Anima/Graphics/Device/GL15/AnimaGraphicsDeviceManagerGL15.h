#ifndef __AE_GRAPHICS_DEVICE_MANAGER_GL15__
#define __AE_GRAPHICS_DEVICE_MANAGER_GL15__

#include "Anima/AnimaPlatform.h"

#if defined(AE_PLATFORM_WIN32)
#   include "Win/AnimaGraphicsDeviceManagerGL15_Win.h"
#elif defined(AE_PLATFORM_OSX)
#   include "Cocoa/AnimaGraphicsDeviceManagerGL15_Cocoa.h"
#elif defined(AE_PLATFORM_LINUX)
#   include "Linux/AnimaGraphicsDeviceManagerGL15_Linux.h"
#endif

#endif
