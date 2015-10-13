#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER__

#include "Anima/Graphics/AnimaGraphicsColor.h"
#include "Anima/Graphics/AnimaGraphicsColorBuffer.h"
#include "Anima/Graphics/AnimaGraphicsDevicePixelBufferDesc.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Math/AnimaMathPoint2.h"
#include "Anima/Math/AnimaMathRectangle.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBuffer : public AE::Graphics::ColorBuffer
			{
			public:
				PixelBuffer(AE::Graphics::Device::PixelBufferDesc const &pixelBufferDesc) :
					AE::Graphics::ColorBuffer(pixelBufferDesc.colorBufferDesc),
					mAllocationType(pixelBufferDesc.allocationType),
					mColorKey(pixelBufferDesc.colorKey),
					mUsesColorKey(pixelBufferDesc.usesColorKey) 
					{
						mBufferType = AE::Graphics::BT_PIXEL_BUFFER;
					}

				virtual ~PixelBuffer() {}

				virtual void					blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> dimensions, AE::Math::Point2<AE::int32> const &destPosition) = 0;
				virtual void*					lock(AE::Graphics::LockType lockType) = 0;
				virtual void					plot(AE::Graphics::Color const &color, AE::Math::Point2<AE::int32> const &position) = 0;
				virtual void					plot32(AE::uint32 const color, AE::Math::Point2<AE::int32> const &position) = 0;
				virtual void					unlock() = 0;

				/***** Inherited from AE::Graphics::ColorBuffer
				AE::Graphics::BufferType		getBufferType();
				AE::Graphics::ColorFormat		getColorFormat();
				void*							getData();
				AE::Math::Point2&				getDimensions();
				*****/

			protected:
				AE::Graphics::AllocationType	mAllocationType;
				AE::Graphics::Color				mColorKey;
				bool							mUsesColorKey;

				/***** Inherited from AE::Graphics::ColorBuffer
				AE::Graphics::BufferType		mBufferType;
				AE::Graphics::ColorFormat		mColorFormat;
				void							*mData;
				AE::Math::Point2				mDimensions;
				*****/
			};
		}
	}
}

#endif