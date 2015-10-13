#ifndef __AE_PLATFORM__
#define __AE_PLATFORM__

// Finds the current platform
#if defined(__WIN32__) || defined(_WIN32)
#	define AE_PLATFORM_WIN32
#elif defined(__APPLE__)
#	define AE_PLATFORM_OSX
#   if defined(MAC_OS_X_VERSION_10_6)
#       define AE_PLATFORM_OSX_MAJOR_VERSION 10
#       define AE_PLATFORM_OSX_MINOR_VERSION 6
#   elif defined(MAC_OS_X_VERSION_10_7)
#       define AE_PLATFORM_OSX_MAJOR_VERSION 10
#       define AE_PLATFORM_OSX_MINOR_VERSION 7
#   endif
#elif defined(__linux__)
#	define AE_PLATFORM_LINUX
#endif

// Finds the compiler type and version.
#if defined(_MSC_VER)
#   define AE_COMPILER_MSVC
#   define AE_COMP_VER _MSC_VER
#elif defined(__GNUC__)
#   define AE_COMPILER_GNUC
#   define AE_COMP_VER (((__GNUC__)*100) + \
		(__GNUC_MINOR__*10) + \
		__GNUC_PATCHLEVEL__)
#else
#   pragma error "No known compiler."
#endif

//----------------------------------------------------------------------------
// Endian Settings
// Set AE_ENDIAN correctly
// Code taken from Boost (endian.hpp)
#if defined(__sparc) || defined(__sparc__) \
   || defined(_POWER) || defined(__powerpc__) \
   || defined(__ppc__) || defined(__hpux) \
   || defined(_MIPSEB) || defined(_POWER) \
   || defined(__s390__)
#	define AE_BIG_ENDIAN
#	define AE_BYTE_ORDER 4321
#elif defined(__i386__) || defined(__alpha__) \
   || defined(__ia64) || defined(__ia64__) \
   || defined(_M_IX86) || defined(_M_IA64) \
   || defined(_M_ALPHA) || defined(__amd64) \
   || defined(__amd64__) || defined(_M_AMD64) \
   || defined(__x86_64) || defined(__x86_64__) \
   || defined(_M_X64)
#	define AE_LITTLE_ENDIAN
#	define AE_BYTE_ORDER 1234
#endif

// Finds the architecture type
#if defined(__x86_64__) || defined (__x86_64) || defined (__amd64__) || defined (__amd64) || defined(_M_X64) || defined(_M_IA64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define AE_ARCHITECTURE_64
#else
#   define AE_ARCHITECTURE_32
#endif



// Disable unicode support on MingW at the moment, poorly supported in stdlibc++
// STLPORT fixes this though so allow if found
// MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLKIT_UNICODE__ in _mingw.h
#if defined(__MINGW32__) && !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__)
#	    define AE_UNICODE_SUPPORT 1
#   else
#       define AE_UNICODE_SUPPORT 0
#   endif
#else
#	define AE_UNICODE_SUPPORT 1
#endif


#if defined ( AE_GCC_VISIBILITY )
/* Until libstdc++ for gcc 4.2 is released, we have to declare all
 * symbols in libstdc++.so externally visible, otherwise we end up
 * with them marked as hidden by -fvisible=hidden.
 *
 * See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=20218
 */
#   pragma GCC visibility push(default)
#endif

extern "C"
{
	#include <sys/stat.h>
}

#ifdef AE_PLATFORM_WIN32
#	include "Platform/AnimaPlatformWin32.h"
#endif

#ifdef AE_PLATFORM_LINUX
#	include "Platform/AnimaPlatformLinux.h"
#endif

#ifdef AE_PLATFORM_OSX
#	include "Platform/AnimaPlatformOSX.h"
#endif

#if defined ( AE_GCC_VISIBILITY )
#   pragma GCC visibility pop
#endif

#endif


