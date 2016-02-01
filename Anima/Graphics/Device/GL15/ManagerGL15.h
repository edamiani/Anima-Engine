#ifndef __AE_GRAPHICS_DEVICE_MANAGER_GL15__
#define __AE_GRAPHICS_DEVICE_MANAGER_GL15__

#include "Anima/Platform.h"

#if defined(AE_PLATFORM_WIN32)
#   include "Anima/Graphics/Device/GL15/Win/ManagerGL15_Win.h"
#elif defined(AE_PLATFORM_OSX)
#   include "Anima/Graphics/Device/GL15/Cocoa/ManagerGL15_Cocoa.h"
#elif defined(AE_PLATFORM_LINUX)
#   include "Anima/Graphics/Device/GL15/Linux/ManagerGL15_Linux.h"
#endif

#endif
