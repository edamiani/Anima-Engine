#ifndef __AE_PLATFORM_OSX__
#define __AE_PLATFORM_OSX__

// A quick define to overcome different names for the same function
#define stricmp strcasecmp

// Always enable unicode support for the moment
// Perhaps disable in old versions of gcc if necessary
#define AE_UNICODE_SUPPORT 1

extern "C" 
{
#   include <unistd.h>
#   include <stddef.h>
#   include <sys/param.h>
#   include <CoreFoundation/CoreFoundation.h>
}

#endif


