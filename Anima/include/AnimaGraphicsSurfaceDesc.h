#ifndef __ANIMA_GRAPHICS_SURFACE_DESC__
#define __ANIMA_GRAPHICS_SURFACE_DESC__

#include "AnimaTypes.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		struct SurfaceDesc
		{
			AE::Graphics::AllocationType	allocationType;
			AE::Graphics::Color				colorKey;
			void *							data;
			AE::Math::Point2<AE::uint>		dimensions;
			AE::Graphics::Device::PixelBufferType
											pixelBufferType;
			AE::Graphics::SurfaceFormat		surfaceFormat;
			bool							usesColorKey;

			SurfaceDesc() :
				allocationType(AE::Graphics::AT_SYSTEM_MEMORY),
				colorKey(0, 0, 0, 0),
				data(0),
				dimensions(0, 0),
				pixelBufferType(AE::Graphics::Device::PBT_OFFSCREEN),
				surfaceFormat(AE::Graphics::SF_UNKNOWN),
				usesColorKey(false) {}
		};
	}
}

#endif