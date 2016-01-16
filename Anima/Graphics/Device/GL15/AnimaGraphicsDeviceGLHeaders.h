#ifndef __AE_GRAPHICS_DEVICE_GL_HEADERS__
#define __AE_GRAPHICS_DEVICE_GL_HEADERS__

#ifdef AE_PLATFORM_WIN32
#   include "GL/glew.h"
#   include "GL/wglew.h"
#   include <gl/GL.h>
#   include <gl/GLU.h>
#elif defined(AE_PLATFORM_OSX)
#   include <GL/glew.h>
#   include <AGL/AGL.h>
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#elif defined(AE_PLATFORM_LINUX)
#   include <GL/glew.h>
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glx.h>
#endif

#endif