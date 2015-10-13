#ifndef __AE_GRAPHICS_DEVICE_TRANSFORMED_PIXEL_BUFFER__
#define __AE_GRAPHICS_DEVICE_TRANSFORMED_PIXEL_BUFFER__

#include "AnimaGraphicsTransformation2dDesc.h"
#include "../Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBuffer;

			class TransformedPixelBuffer
			{
			public:
				TransformedPixelBuffer(AE::Graphics::Device::PixelBuffer *pixelBuffer, const AE::Graphics::Transformation2dDesc &transformation2dDesc)
					: mPixelBuffer(pixelBuffer), mPosition(transformation2dDesc.position),
					  mRotation(transformation2dDesc.rotation), mScale(transformation2dDesc.scale),
					  mZDepth(transformation2dDesc.zDepth) { }

				virtual ~TransformedPixelBuffer() {}

			protected:
				AE::Graphics::Device::PixelBuffer	*mPixelBuffer;
				AE::Math::Point2<AE::int32>			mPosition;
				AE::Real							mRotation;
				AE::Math::Point2<AE::int32>			mScale;
				AE::Real							mZDepth;
			};
		}
	}
}

#endif