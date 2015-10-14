#ifndef __AE_GRAPHICS_DEVICE_STAGE_PIXEL_OPERATIONS__
#define __AE_GRAPHICS_DEVICE_STAGE_PIXEL_OPERATIONS__

#include "AnimaGraphicsDeviceStage.h"
#include "AnimaGraphicsDevicePixelBuffer.h"

#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Math/AnimaMathPoint2.h"
#include "Anima/Math/AnimaMathRectangle.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StagePixelOperations : public AE::Graphics::Device::Stage
			{
			public:
				StagePixelOperations() {}
				~StagePixelOperations() {}

				virtual AE::Math::Rectangle clipPixelBuffer(AE::Graphics::Device::PixelBuffer *source, AE::Graphics::Device::PixelBuffer *destination, const AE::Math::Point2<AE::Real> &position);
				virtual void packPixelBuffer(AE::Graphics::Device::PixelBuffer *source, AE::Graphics::SurfaceFormat packedFormat);
				virtual void unpackPixelBuffer(AE::Graphics::Device::PixelBuffer *source, AE::Graphics::SurfaceFormat unpackedFormat);

			protected:
			};
		}
	}
}

#endif