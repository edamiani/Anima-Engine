#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL21__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL21__

#include "AnimaPlatform.h"

#if defined(AE_PLATFORM_WIN32)
#   include "AnimaGraphicsDeviceContextGL21_Win.h"
#elif defined(AE_PLATFORM_OSX)
#   include "AnimaGraphicsDeviceContextGL21_Cocoa.h"
#elif defined(AE_PLATFORM_LINUX)
#   include "AnimaGraphicsDeviceContextGL21_Linux.h"
#endif

#endif