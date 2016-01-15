#ifndef __AE_GRAPHICS_OPENGL_EXTENSIONS__
#define __AE_GRAPHICS_OPENGL_EXTENSIONS__

#ifdef WIN32
	#include "../../Dependencies/gl/glext.h"
	#include "../../Dependencies/gl/wglext.h"

	// GL_EXT_draw_range_elements (1.2)
	extern PFNGLDRAWRANGEELEMENTSPROC		glDrawRangeElements;

	// GL_EXT_multi_draw_arrays (1.4)
	extern PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays;
	extern PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements;

	// GL_ARB_multitexture (1.4)
	extern PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture;

	// GL_ARB_window_pos (1.4)
	extern PFNGLWINDOWPOS2IPROC				glWindowPos2i;

	// GL_ARB_vertex_buffer_object(1.5)
	extern "C" PFNGLBINDBUFFERPROC				glBindBuffer;
	extern "C" PFNGLBUFFERDATAPROC				glBufferData;
	extern "C" PFNGLBUFFERSUBDATAPROC			glBufferSubData;
	extern "C" PFNGLDELETEBUFFERSPROC			glDeleteBuffers;
	extern "C" PFNGLGENBUFFERSPROC				glGenBuffers;
	extern "C" PFNGLGETBUFFERPARAMETERIVPROC	glGetBufferParameteriv;
	extern "C" PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv;
	extern "C" PFNGLGETBUFFERSUBDATAPROC		glGetBufferSubData;
	extern "C" PFNGLISBUFFERPROC				glIsBuffer;
	extern "C" PFNGLMAPBUFFERPROC				glMapBuffer;
	extern "C" PFNGLUNMAPBUFFERPROC				glUnmapBuffer;

#elif defined AE_PLATFORM_OSX
	#include "../../Dependencies/gl/glext.h"
	#include "../../Dependencies/gl/glxext.h"

	// GL_EXT_draw_range_elements (1.2)
	extern PFNGLDRAWRANGEELEMENTSPROC		glDrawRangeElements;

	// GL_EXT_multi_draw_arrays (1.4)
	extern PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays;
	extern PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements;

	// GL_ARB_multitexture (1.4)
	extern PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture;

	// GL_ARB_window_pos (1.4)
	extern PFNGLWINDOWPOS2IPROC				glWindowPos2i;

	// GL_ARB_vertex_buffer_object(1.5)
	extern PFNGLBINDBUFFERPROC				glBindBuffer;
	extern PFNGLBUFFERDATAPROC				glBufferData;
	extern PFNGLBUFFERSUBDATAPROC			glBufferSubData;
	extern PFNGLDELETEBUFFERSPROC			glDeleteBuffers;
	extern PFNGLGENBUFFERSPROC				glGenBuffers;
	extern PFNGLGETBUFFERPARAMETERIVPROC	glGetBufferParameteriv;
	extern PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv;
	extern PFNGLGETBUFFERSUBDATAPROC		glGetBufferSubData;
	extern PFNGLISBUFFERPROC				glIsBuffer;
	extern PFNGLMAPBUFFERPROC				glMapBuffer;
	extern PFNGLUNMAPBUFFERPROC				glUnmapBuffer;

#elif defined AE_PLATFORM_LINUX
	#include "../../Dependencies/gl/glext.h"

	// GL_EXT_draw_range_elements (1.2)
//	extern PFNGLDRAWRANGEELEMENTSPROC		glDrawRangeElements; // I think Linux already has this one

	// GL_EXT_multi_draw_arrays (1.4)
	extern PFNGLMULTIDRAWARRAYSPROC			glMultiDrawArrays;
	extern PFNGLMULTIDRAWELEMENTSPROC		glMultiDrawElements;

	// GL_ARB_multitexture (1.4)
//	extern PFNGLCLIENTACTIVETEXTUREPROC		glClientActiveTexture; // I think Linux already has this one

	// GL_ARB_window_pos (1.4)
	extern PFNGLWINDOWPOS2IPROC				glWindowPos2i;

	// GL_ARB_vertex_buffer_object(1.5)
	extern PFNGLBINDBUFFERPROC				glBindBuffer;
	extern PFNGLBUFFERDATAPROC				glBufferData;
	extern PFNGLBUFFERSUBDATAPROC			glBufferSubData;
	extern PFNGLDELETEBUFFERSPROC			glDeleteBuffers;
	extern PFNGLGENBUFFERSPROC				glGenBuffers;
	extern PFNGLGETBUFFERPARAMETERIVPROC	glGetBufferParameteriv;
	extern PFNGLGETBUFFERPOINTERVPROC		glGetBufferPointerv;
	extern PFNGLGETBUFFERSUBDATAPROC		glGetBufferSubData;
	extern PFNGLISBUFFERPROC				glIsBuffer;
	extern PFNGLMAPBUFFERPROC				glMapBuffer;
	extern PFNGLUNMAPBUFFERPROC				glUnmapBuffer;

#endif

#endif
