#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL1_5__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL1_5__

#include "AnimaPlatform.h"

#if defined(AE_PLATFORM_WIN32)
#   include "AnimaGraphicsDeviceContextGL1_5_Win.h"
#elif defined(AE_PLATFORM_OSX)
#   include "AnimaGraphicsDeviceContextGL1_5_Cocoa.h"
#elif defined(AE_PLATFORM_LINUX)
#   include "AnimaGraphicsDeviceContextGL1_5_Linux.h"
#endif

#endif