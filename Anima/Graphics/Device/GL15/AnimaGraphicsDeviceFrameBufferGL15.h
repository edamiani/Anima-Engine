#ifndef __AE_GRAPHICS_DEVICE_FRAME_BUFFER_GL15__
#define __AE_GRAPHICS_DEVICE_FRAME_BUFFER_GL15__

#include "Anima/Graphics/Device/AnimaGraphicsDeviceFrameBuffer.h"

#include "Anima/AnimaPlatform.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceGLHeaders.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePixelBufferDesc.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL15;

			class FrameBufferGL15 : public AE::Graphics::Device::FrameBuffer
			{
			public:
				FrameBufferGL15(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc);
				~FrameBufferGL15();

				/***** Inherited from AE::Graphics::Device::PixelBuffer *****/
				void							blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition);
				void*							getData();
				void*							lock(AE::Graphics::LockType lockType);
				void							plot(const AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &position);
				void							plot32(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position);
				void							unlock();

				/***** Inherited from AE::Graphics::ColorBuffer
				AE::Graphics::ColorFormat		getColorFormat();
				void*							getData();
				AE::Math::Point2&				getDimensions();
				AE::Math::Point2&				getRowOrder();
				*****/

			private:
				GLenum							mPixelFormatGL;
				GLenum							mTypeGL;

				friend	AE::Graphics::Device::ContextGL15;

				/***** Inherited from AE::Graphics::Device::PixelBuffer
				AE::Graphics::AllocationType	mAllocationType;
				AE::Graphics::Color				mColorKey;
				AE::Graphics::Device::PixelBufferType
												mPixelBufferType;
				bool							mUsesColorKey;
				*****/

				/***** Inherited from AE::Graphics::ColorBuffer
				AE::Graphics::ColorFormat		mColorFormat;
				void							*mData;
				AE::Math::Point2				mDimensions;
				AE::Graphics::RowOrder			mRowOrder;
				*****/
			};
		}
	}
}

#endif