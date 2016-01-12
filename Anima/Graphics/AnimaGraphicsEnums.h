#ifndef __AE_GRAPHICS_ENUMS__
#define __AE_GRAPHICS_ENUMS__

#include "../AnimaEnums.h"

namespace AE
{
	namespace Graphics
	{
		enum AllocationType
		{
			AT_MANAGED_MEMORY,
			AT_SYSTEM_MEMORY,
			AT_VIDEO_MEMORY
		};

		enum BorderPosition
		{
			BP_CENTER,
			BP_INSIDE,
			BP_OUTSIDE
		};

		// These are set from user's perspective
		enum BufferChangeFrequency
		{
			BCF_STATIC,
			BCF_DYNAMIC,
			BCF_STREAM
		};

		enum BufferType
		{
			BT_ACCUMULATION_BUFFER,
			BT_COLOR_BUFFER,
			BT_DEPTH_BUFFER,
			BT_FRAME_BUFFER,
			BT_INDEX_BUFFER,
			BT_PIXEL_BUFFER,
			BT_STENCIL_BUFFER,
			BT_VERTEX_BUFFER
		};

		// These are set from user's perspective
		enum BufferUsage
		{
			BU_USER_WRITE,
			BU_USER_READ,
			BU_CPU_COPY,
		};

		enum ColorFormat
		{
			CF_UNKNOWN,
			CF_A8R8G8B8,
			CF_X8R8G8B8,
			CF_R8G8B8A8,
			CF_R8G8B8X8,
			CF_A1R5G5B5,
			CF_X1R5G5B5,
			CF_R8G8B8,
			CF_B8G8R8,
			CF_R5G6B5,
			CF_B5G6R5,
			CF_PALLETE8
		};

		enum FontOptions
		{
			FO_NO_OPTIONS	= 0x0000,
			FO_ANTIALIASING = 0x0001,
			FO_MONOCHROME	= 0x0002,
			FO_USE_KERNING	= 0x0004,
			FO_CELL_TYPE	= 0x0008
		};

		enum FontType
		{
			FT_IMAGE,
			FT_TRUETYPE
		};

		enum GeometryType
		{
			GT_ARC,
			GT_CIRCLE,
			GT_DONUT,
			GT_ELLIPSE,
			GT_LINE,
			GT_PIE,
			GT_RECTANGLE,
			GT_SPLINE,
			GT_TRIANGLE
		};

		enum GraphicsManagerOptions
		{
			GMO_SOFTWARE	= 0x0000,
			GMO_D3D9		= 0x0001,
			GMO_D3D10		= 0x0002,
			GMO_D3D11		= 0x0004,
			GMO_ALLEGRO		= 0x0008,
			GMO_OGRE		= 0x0010,
			GMO_GL15		= 0x0020,
			GMO_GL21		= 0x0040,
			GMO_GLES10		= 0x0080,
			GMO_GLES20		= 0x0100,
			GMO_FONT_FT		= 0x0200,
			GMO_IMAGE_PNG	= 0x1000,
			GMO_IMAGE_JPG	= 0x1001
		};

		enum ImageType
		{
			IT_UNKNOWN	= 0x0000,
			IT_JPEG		= 0x0001,
			IT_PNG		= 0x0002,
			IT_RAW		= 0x0004,
			IT_TGA		= 0x0008,
			IT_TIFF		= 0x0010
		};

		enum LockType
		{
			LT_DISCARD,
			LT_NO_DIRTY_UPDATE,
			LT_NOSYSLOCK,
			LT_READONLY,
			LT_WRITEONLY,
			LT_READWRITE
		};

		enum NoOptions
		{
			NO_OPTIONS
		};

		enum RenderOperationType
		{
			ROT_POINT_LIST,
			ROT_LINE_LIST,
			ROT_LINE_STRIP,
			ROT_TRIANGLE_LIST,
			ROT_TRIANGLE_STRIP,
			ROT_TRIANGLE_FAN
		};

		enum RenderType
		{
			RT_NONE,
			RT_DIRECT3D9,
			RT_DIRECT3D10,
			RT_DIRECT3D11,
			RT_OPENGL
		};

		enum SurfaceFormat
		{
			SF_UNKNOWN,
			SF_A8R8G8B8,
			SF_X8R8G8B8,
			SF_R8G8B8A8,
			SF_R8G8B8X8,
			SF_A1R5G5B5,
			SF_X1R5G5B5,
			SF_R8G8B8,
			SF_R5G6B5,
			SF_P8 // 'P' stands for Pallete
		};

		enum VertexElement
		{
			VE_POSITION = 1,
			VE_BLEND_WEIGHT0 = 2,
			VE_BLEND_WEIGHT1 = 4,
			VE_BLEND_WEIGHT2 = 8,
			VE_BLEND_WEIGHT3 = 16,
			VE_NORMAL = 32,
			VE_DIFFUSE = 64,
			VE_SPECULAR = 128,
			VE_TEX_COORD0 = 256,
			VE_TEX_COORD1 = 512,
			VE_TEX_COORD2 = 1024,
			VE_TEX_COORD3 = 2048
		};

		namespace Device
		{
			// These are set from user's perspective
			enum BufferUsage
			{
				BU_DYNAMIC_WRITE,
				BU_DYNAMIC_READ,
				BU_DYNAMIC_COPY,
				BU_STATIC_WRITE,
				BU_STATIC_READ,
				BU_STATIC_COPY,
				BU_STREAM_WRITE,
				BU_STREAM_READ,
				BU_STREAM_COPY,
			};

			enum ContextOption
			{
				CO_NO_OPTIONS =	0x0000,
				CO_SOFTWARE =	0x0001,
				CO_HARDWARE =	0x0002,
				CO_OPENGL =		0x0004,
				CO_DX9 =		0x0008,
				CO_OPENGL3 =	0x0010
			};

			enum DriverType
			{
				DT_NONE,
				DT_D3D9,
				DT_D3D10,
				DT_D3D11,
				DT_GL_15,
				DT_GL_20,
				DT_GL_21,
				DT_GL_30
			};

			enum PixelBufferType
			{
				PBT_OFFSCREEN = 0,
				PBT_FRAME_BUFFER
			};

			enum StageType
			{
				ST_CLIPPING_2D,
				ST_DOMAIN_SHADER,
				ST_FRAGMENT_SHADER,
				ST_GEOMETRY_SHADER,
				ST_HULL_SHADER,
				ST_INPUT_2D,
				ST_OUTPUT_MERGER,
				ST_PIXEL_OPERATIONS,
				ST_RASTERIZER,
				ST_STREAM_OUTPUT,
				ST_TESSELATOR,
				ST_TRANSFORMATION_2D,
				ST_VERTEX_SHADER
			};

			enum SubpipelineType
			{
				SPLT_2D_OPERATIONS,
				SPLT_3D_OPERATIONS,
				SPLT_RASTERIZER
			};
		}
	}
}

#endif