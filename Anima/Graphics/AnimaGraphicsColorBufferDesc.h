#ifndef __ANIMA_GRAPHICS_COLOR_BUFFER_DESC__
#define __ANIMA_GRAPHICS_COLOR_BUFFER_DESC__

#include "../AnimaTypes.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		struct ColorBufferDesc
		{
			AE::Graphics::ColorFormat				colorFormat;
			void									*data;
			AE::Math::Point2<AE::uint>				dimensions;

			ColorBufferDesc() :
				colorFormat(AE::Graphics::CF_UNKNOWN),
				data(0),
				dimensions(0, 0) { }
		};
	}
}

#endif