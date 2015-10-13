#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL15__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL15__

#include "AnimaPlatform.h"

#if defined(AE_PLATFORM_WIN32)
#   include "AnimaGraphicsDeviceContextGL15_Win.h"
#elif defined(AE_PLATFORM_OSX)
#   include "AnimaGraphicsDeviceContextGL15_Cocoa.h"
#elif defined(AE_PLATFORM_LINUX)
#   include "AnimaGraphicsDeviceContextGL15_Linux.h"
#endif

#endif