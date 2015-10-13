#ifndef __ANIMA_GRAPHICS_DEVICE_COLOR_BUFFER_DESC__
#define __ANIMA_GRAPHICS_DEVICE_COLOR_BUFFER_DESC__

#include "Anima/Graphics/AnimaGraphicsColor.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/AnimaTypes.h"
#include "Anima/Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		class Image;

		namespace Device
		{
			struct ColorBufferDesc
			{
				AE::Graphics::ColorFormat				colorFormat;
				void *									data;
				AE::Math::Point2<AE::int32>				dimensions;
				//AE::Graphics::RowOrder					rowOrder;
				AE::Graphics::Image						*sourceImage;
				AE::Graphics::Device::BufferUsage		usage;

				ColorBufferDesc() :
					colorFormat(AE::Graphics::CF_UNKNOWN),
					data(0),
					dimensions(0, 0),
					//rowOrder(AE::Graphics::RO_TOP_DOWN),
					sourceImage(0),
					usage(AE::Graphics::Device::BU_STATIC_READ) {}
			};
		}
	}
}

#endif