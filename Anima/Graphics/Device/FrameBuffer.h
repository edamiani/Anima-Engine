#ifndef __AE_GRAPHICS_DEVICE_FRAME_BUFFER__
#define __AE_GRAPHICS_DEVICE_FRAME_BUFFER__

#include "Anima/Graphics/Device/PixelBuffer.h"
#include "Anima/Graphics/Device/PixelBufferDesc.h"

#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"
#include "Anima/Math/Rectangle.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class FrameBuffer : public AE::Graphics::Device::PixelBuffer
			{
			public:
				FrameBuffer(AE::Graphics::Device::PixelBufferDesc const &pixelBufferDesc) :
					AE::Graphics::Device::PixelBuffer(pixelBufferDesc)
				{
					mBufferType = AE::Graphics::BT_FRAME_BUFFER;
				}

				virtual ~FrameBuffer() {}

				/***** Inherited from AE::Graphics::Device::PixelBuffer
				virtual void					blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> dimensions, AE::Math::Point2<AE::int32> const &destPosition) = 0;
				virtual void					lock(AE::Graphics::LockType lockType) = 0;
				virtual void					plot(const AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &position) = 0;
				virtual void					plot32(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position) = 0;
				virtual void					unlock() = 0;
				*****/

				/***** Inherited from AE::Graphics::ColorBuffer
				AE::Graphics::BufferType		getBufferType();
				AE::Graphics::ColorFormat		getColorFormat();
				void*							getData();
				AE::Math::Point2&				getDimensions();
				*****/

			protected:
				/***** Inherited from AE::Graphics::Device::PixelBuffer
				AE::Graphics::AllocationType	mAllocationType;
				AE::Graphics::Color				mColorKey;
				bool							mUsesColorKey;
				*****/

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