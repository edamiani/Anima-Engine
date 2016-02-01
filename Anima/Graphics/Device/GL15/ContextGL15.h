#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL15__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL15__

#include "Anima/Platform.h"

#if defined(AE_PLATFORM_WIN32)
#   include "Anima/Graphics/Device/GL15/Win/ContextGL15_Win.h"
#elif defined(AE_PLATFORM_OSX)
#   include "Anima/Graphics/Device/GL15/Cocoa/ContextGL15_Cocoa.h"
#elif defined(AE_PLATFORM_LINUX)
#   include "Anima/Graphics/Device/GL15/Linux/ContextGL15_Linux.h"
#endif

#endif