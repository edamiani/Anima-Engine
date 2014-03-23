#ifndef __AE_TYPES__
#define __AE_TYPES__

#include "AnimaPlatform.h"

#include <cassert>
#include <iostream>
#include <string>

namespace AE
{
	typedef unsigned char byte;
	typedef unsigned char uchar;
	typedef unsigned short ushort;
	typedef unsigned int uint;
	typedef unsigned long ulong;

	// Integer formats of fixed bit width
	typedef unsigned int flags;
	typedef unsigned int uint32;
	typedef unsigned short uint16;
	typedef unsigned char uint8;
	typedef int int32;
	typedef short int16;
	typedef char int8;

	// define uint64 type
	#ifdef AE_COMPILER_MSVC
		typedef unsigned __int64 uint64;
		typedef __int64 int64;
	#else
		typedef unsigned long long uint64;
		typedef long long int64;
	#endif

    // define the real number values to be used
    // default to use 'float' unless precompiler option set
    #if AE_DOUBLE_PRECISION
        typedef double Real;
    #else
        typedef float Real;
    #endif

	namespace Graphics
	{
		typedef uint8 color8;
		typedef uint16 color16;
		typedef uint32 color32;

		typedef uint32 RGBA;
		typedef uint32 ARGB;
		typedef uint32 ABGR;
		typedef uint32 BGRA;
	}
}

#endif


