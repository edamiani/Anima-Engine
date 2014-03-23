#ifndef __ANIMA_PREREQUISITES__
#define __ANIMA_PREREQUISITES__

// Platform-specific stuff
#ifndef AE_DOUBLE_PRECISION
#define AE_DOUBLE_PRECISION 0
#endif

/* Initial platform/compiler-related stuff to set.
*/
#define AE_PLATFORM_WIN32 1
#define AE_PLATFORM_LINUX 2
#define AE_PLATFORM_APPLE 3
#define AE_PLATFORM_SYMBIAN 4
#define AE_PLATFORM_IPHONE 5

#define AE_COMPILER_MSVC 1
#define AE_COMPILER_GNUC 2
#define AE_COMPILER_BORL 3
#define AE_COMPILER_WINSCW 4
#define AE_COMPILER_GCCE 5

#define AE_ENDIAN_LITTLE 1
#define AE_ENDIAN_BIG 2

#define AE_ARCHITECTURE_32 1
#define AE_ARCHITECTURE_64 2

/* Finds the compiler type and version.
*/
#if defined( __GCCE__ )
#   define AE_COMPILER AE_COMPILER_GCCE
#   define AE_COMP_VER _MSC_VER
//#	include <staticlibinit_gcce.h> // This is a GCCE toolchain workaround needed when compiling with GCCE 
#elif defined( __WINSCW__ )
#   define AE_COMPILER AE_COMPILER_WINSCW
#   define AE_COMP_VER _MSC_VER
#elif defined( _MSC_VER )
#   define AE_COMPILER AE_COMPILER_MSVC
#   define AE_COMP_VER _MSC_VER
#elif defined( __GNUC__ )
#   define AE_COMPILER AE_COMPILER_GNUC
#   define AE_COMP_VER (((__GNUC__)*100) + \
        (__GNUC_MINOR__*10) + \
        __GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define AE_COMPILER AE_COMPILER_BORL
#   define AE_COMP_VER __BCPLUSPLUS__
#   define __FUNCTION__ __FUNC__ 
#else
#   pragma error "No known compiler. Abort! Abort!"

#endif

/* See if we can use __forceinline or if we need to use __inline instead */
#if AE_COMPILER == AE_COMPILER_MSVC
#   if AE_COMP_VER >= 1200
#       define FORCEINLINE __forceinline
#   endif
#elif defined(__MINGW32__)
#   if !defined(FORCEINLINE)
#       define FORCEINLINE __inline
#   endif
#else
#   define FORCEINLINE __inline
#endif

/* Finds the current platform */

#if defined( __SYMBIAN32__ ) 
#   define AE_PLATFORM AE_PLATFORM_SYMBIAN
#elif defined( __WIN32__ ) || defined( _WIN32 )
#   define AE_PLATFORM AE_PLATFORM_WIN32
#elif defined( __APPLE_CC__)
    // Device                                                     Simulator
    // Both requiring OS version 3.0 or greater
#   if __ENVIRONMENT_IPHONE_OS_VERSION_MIN_REQUIRED__ >= 30000 || __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
#       define AE_PLATFORM AE_PLATFORM_IPHONE
#   else
#       define AE_PLATFORM AE_PLATFORM_APPLE
#   endif
#else
#   define AE_PLATFORM AE_PLATFORM_LINUX
#endif

    /* Find the arch type */
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define AE_ARCH_TYPE AE_ARCHITECTURE_64
#else
#   define AE_ARCH_TYPE AE_ARCHITECTURE_32
#endif

// For generating compiler warnings - should work on any compiler
// As a side note, if you start your message with 'Warning: ', the MSVC
// IDE actually does catch a warning :)
#define AE_QUOTE_INPLACE(x) # x
#define AE_QUOTE(x) AE_QUOTE_INPLACE(x)
#define AE_WARN( x )  message( __FILE__ "(" QUOTE( __LINE__ ) ") : " x "\n" )

//----------------------------------------------------------------------------
// Windows Settings
#if AE_PLATFORM == AE_PLATFORM_WIN32

// If we're not including this from a client build, specify that the stuff
// should get exported. Otherwise, import it.
#	if defined( AE_STATIC_LIB )
		// Linux compilers don't have symbol import/export directives.
#   	define _AnimaExport
#   	define _AnimaPrivate
#   else
#   	if defined( AE_NONCLIENT_BUILD )
#       	define _AnimaExport __declspec( dllexport )
#   	else
#           if defined( __MINGW32__ )
#               define _AnimaExport
#           else
#       	    define _AnimaExport __declspec( dllimport )
#           endif
#   	endif
#   	define _AnimaPrivate
#	endif
// Win32 compilers use _DEBUG for specifying debug builds.
#   ifdef _DEBUG
#       define AE_DEBUG_MODE 1
#   else
#       define AE_DEBUG_MODE 0
#   endif

// Disable unicode support on MingW at the moment, poorly supported in stdlibc++
// STLPORT fixes this though so allow if found
// MinGW C++ Toolkit supports unicode and sets the define __MINGW32_TOOLKIT_UNICODE__ in _mingw.h
#if defined( __MINGW32__ ) && !defined(_STLPORT_VERSION)
#   include<_mingw.h>
#   if defined(__MINGW32_TOOLBOX_UNICODE__)
#	    define AE_UNICODE_SUPPORT 1
#   else
#       define AE_UNICODE_SUPPORT 0
#   endif
#else
#	define AE_UNICODE_SUPPORT 1
#endif

#endif
//----------------------------------------------------------------------------
// Symbian Settings
#if AE_PLATFORM == AE_PLATFORM_SYMBIAN
#	define AE_UNICODE_SUPPORT 1
#   define AE_DEBUG_MODE 0
#   define _AnimaExport
#   define _AnimaPrivate
#	define CLOCKS_PER_SEC  1000
// pragma def were found here: http://www.inf.pucrs.br/~eduardob/disciplinas/SistEmbarcados/Mobile/Nokia/Tools/Carbide_vs/WINSCW/Help/PDF/C_Compilers_Reference_3.2.pdf
#	pragma warn_unusedarg off
#	pragma warn_emptydecl off
#	pragma warn_possunwant off
#endif
//----------------------------------------------------------------------------
// Linux/Apple Settings
#if AE_PLATFORM == AE_PLATFORM_LINUX || AE_PLATFORM == AE_PLATFORM_APPLE || AE_PLATFORM == AE_PLATFORM_IPHONE

// Enable GCC symbol visibility
#   if defined( AE_GCC_VISIBILITY )
#       define _AnimaExport  __attribute__ ((visibility("default")))
#       define _AnimaPrivate __attribute__ ((visibility("hidden")))
#   else
#       define _AnimaExport
#       define _AnimaPrivate
#   endif

// A quick define to overcome different names for the same function
#   define stricmp strcasecmp

// Unlike the Win32 compilers, Linux compilers seem to use DEBUG for when
// specifying a debug build.
// (??? this is wrong, on Linux debug builds aren't marked in any way unless
// you mark it yourself any way you like it -- zap ???)
#   ifdef DEBUG
#       define AE_DEBUG_MODE 1
#   else
#       define AE_DEBUG_MODE 0
#   endif

#if AE_PLATFORM == AE_PLATFORM_APPLE
    #define AE_PLATFORM_LIB "AnimaPlatform.bundle"
#elif AE_PLATFORM == AE_PLATFORM_IPHONE
    #define AE_PLATFORM_LIB "AnimaPlatform.a"
#else //AE_PLATFORM_LINUX
    #define AE_PLATFORM_LIB "libAnimaPlatform.so"
#endif

// Always enable unicode support for the moment
// Perhaps disable in old versions of gcc if necessary
#define AE_UNICODE_SUPPORT 1

#endif

//For apple, we always have a custom config.h file
#if AE_PLATFORM == AE_PLATFORM_APPLE
#    include "config.h"
#endif

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Endian Settings
// check for BIG_ENDIAN config flag, set AE_ENDIAN correctly
#ifdef AE_CONFIG_BIG_ENDIAN
#    define AE_ENDIAN AE_ENDIAN_BIG
#else
#    define AE_ENDIAN AE_ENDIAN_LITTLE
#endif

// Integer formats of fixed bit width
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;
typedef int int32;
typedef short int16;
typedef char int8;
// define uint64 type
#if AE_COMPILER == AE_COMPILER_MSVC
	typedef unsigned __int64 uint64;
	typedef __int64 int64;
#else
	typedef unsigned long long uint64;
	typedef long long int64;
#endif

// configure memory tracking
#if AE_DEBUG_MODE 
#	if AE_MEMORY_TRACKER_DEBUG_MODE
#		define AE_MEMORY_TRACKER 1
#	else
#		define AE_MEMORY_TRACKER 0
#	endif
#else
#	if AE_MEMORY_TRACKER_RELEASE_MODE
#		define AE_MEMORY_TRACKER 1
#	else
#		define AE_MEMORY_TRACKER 0
#	endif
#endif

namespace AE
{
    // Define Anima version
    /*#define AE_VERSION_MAJOR 1
    #define AE_VERSION_MINOR 7
    #define AE_VERSION_PATCH 0
	#define AE_VERSION_SUFFIX "RC1"
    #define AE_VERSION_NAME "Cthugha"

    #define AE_VERSION    ((AE_VERSION_MAJOR << 16) | (AE_VERSION_MINOR << 8) | AE_VERSION_PATCH)*/

    // define the real number values to be used
    // default to use 'float' unless precompiler option set
    #if AE_DOUBLE_PRECISION == 1
		/** Software floating point type.
		@note Not valid as a pointer to GPU buffers / parameters
		*/
        typedef double Real;
    #else
		/** Software floating point type.
		@note Not valid as a pointer to GPU buffers / parameters
		*/
        typedef float Real;
    #endif

    #if AE_COMPILER == AE_COMPILER_GNUC && AE_COMP_VER >= 310 && !defined(STLPORT)
	#   if AE_COMP_VER >= 430
	#       define HashMap ::std::tr1::unordered_map
	#		define HashSet ::std::tr1::unordered_set
	#    else
	#       define HashMap ::__gnu_cxx::hash_map
	#       define HashSet ::__gnu_cxx::hash_set
	#    endif
    #else
    #   if AE_COMPILER == AE_COMPILER_MSVC
    #       if AE_COMP_VER >= 1600 // VC++ 10.0
	#			define HashMap ::std::tr1::unordered_map
	#           define HashSet ::std::tr1::unordered_set
	#		elif AE_COMP_VER > 1300 && !defined(_STLP_MSVC)
    #           define HashMap ::stdext::hash_map
	#           define HashSet ::stdext::hash_set
    #       else
    #           define HashMap ::std::hash_map
	#           define HashSet ::std::hash_set
    #       endif
    #   else
    #       define HashMap ::std::hash_map
	#       define HashSet ::std::hash_set
    #   endif
    #endif

    /** In order to avoid finger-aches :)
    */
    typedef unsigned char uchar;
    typedef unsigned short ushort;
    typedef unsigned int uint;
	typedef unsigned long ulong;


	// Useful threading defines
	// KEEP IT???????
	//#include "Threading/OgreThreadDefines.h"

	// Pre-declare classes
	// Allows use of pointers in header files without including individual .h
	// so decreases dependencies between files
	class Framework;

	namespace Entity
	{
		class Dynamic;
		struct DynamicEntityDesc;
		struct EntityDesc;
		class Kinematic;
		struct KinematicEntityDesc;
		class Manager;
		struct StaticEntityDesc;
	}

    namespace Graphics
	{
		class ColorValue;
		class Font;
		class IndexBuffer;
		class Manager;
		class Mesh;
		class Sprite;
		struct SpriteDesc;
		class VertexBuffer;
	}

	namespace Gui
	{
		class Button;
		class Callback;
		class Listener;
		class Manager;
		class Text;
		class TextInput;
		class Window;
	}

	namespace Input
	{
		struct Axis;
		class  Device;
		class  Joystick;
		struct JoystickEvent;
		struct JoyStickState;
		class  Keyboard;
		struct KeyEvent;
		class  Manager;
		class  Mouse;
		struct MouseEvent;
		struct Pov;
		struct Slider;
	}

	namespace Math
	{
		class AxisAlignedBox;
		class Matrix4;
		class Quaternion;
		class Vector2;
		class Vector3;
		class Vector4;
	}

	namespace OS
	{
		class Window;
		struct WindowMetrics;
	}

	namespace Physics
	{
		class CollisionShape;
		struct CollisionShapeDesc;
		class Dynamic;
		class Kinematic;
		class Manager;
		class RigidBody;
		struct RigidBodyDesc;
		class Static;
	}

	namespace Scene
	{
		class X3DBindableNode;
		class X3DBoundedObject;
		class X3DChildNode;
		class X3DGeometricPropertyNode;
		class X3DGeometryNode;
		class X3DGroupingNode;
		class X3DInfoNode;
		class X3DLayerNode;
		class X3DMetadataObject;
		class X3DNode;
		class X3DNormalNode;
		class X3DPrototypeInstance;
		class X3DSensorNode;
		class X3DTextureCoordinateNode;
		class X3DVertexAttributeNode;
		class X3DViewportNode;
		class  X3DCamera;
		struct X3DCameraDesc;
		class X3DCoordinate;
		struct X3DLayer;
		struct X3DLightDesc;
		class  X3DManager;
		class  X3DNode;
		struct X3DNodeDesc;
		struct X3DViewport;
	}

	namespace Xml
	{
		class Document;
		class Element;
		class Manager;
	}
}

/* Include all the standard header *after* all the configuration
settings have been made.
*/

#ifdef __BORLANDC__
    #define __STD_ALGORITHM
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

#include <cassert>
#include <ctime>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <vector>

// Note - not in the original STL, but exists in SGI STL and STLport
// For gcc 4.3 see http://gcc.gnu.org/gcc-4.3/changes.html
#if (AE_COMPILER == AE_COMPILER_GNUC) && !defined(STLPORT)
#   if AE_COMP_VER >= 430
#       include <tr1/unordered_map>
#       include <tr1/unordered_set> 
#   else
#       include <ext/hash_map>
#       include <ext/hash_set>
#   endif
#else
#   if (AE_COMPILER == AE_COMPILER_MSVC) && !defined(STLPORT) && AE_COMP_VER >= 1600 // VC++ 10.0
#    	include <unordered_map>
#    	include <unordered_set>
#	else
#   	include <hash_set>
#   	include <hash_map>
#	endif
#endif 

#ifdef __BORLANDC__
namespace AE
{
    using namespace std;
}
#endif

extern "C" 
{
#   include <sys/types.h>
#   include <sys/stat.h>
}

#if AE_PLATFORM == AE_PLATFORM_WIN32
#  undef min
#  undef max
#  if defined( __MINGW32__ )
#    include <unistd.h>
#  endif
#endif

#if AE_PLATFORM == AE_PLATFORM_LINUX
extern "C" 
{
#   include <unistd.h>
#   include <dlfcn.h>
}
#endif

#if AE_PLATFORM == AE_PLATFORM_APPLE || AE_PLATFORM == AE_PLATFORM_IPHONE
extern "C" 
{
#   include <unistd.h>
#	include <stddef.h>
#   include <sys/param.h>
#   include <CoreFoundation/CoreFoundation.h>
}
#endif

/*#if AE_THREAD_SUPPORT
#	if !defined(NOMINMAX) && defined(_MSC_VER)
#		define NOMINMAX // required to stop windows.h messing up std::min
#	endif
#   include "Threading/OgreThreadHeaders.h"
#endif*/

#if defined ( AE_GCC_VISIBILITY )
#   pragma GCC visibility pop
#endif

#endif


