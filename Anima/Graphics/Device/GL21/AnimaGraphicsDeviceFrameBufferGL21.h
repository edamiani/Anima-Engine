#ifndef __AE_GRAPHICS_DEVICE_FRAME_BUFFER_GL21__
#define __AE_GRAPHICS_DEVICE_FRAME_BUFFER_GL21__

#include "AnimaGraphicsDeviceFrameBuffer.h"

#include "AnimaGraphicsDeviceGLHeaders.h"
#include "AnimaGraphicsDevicePixelBufferDesc.h"
#include "AnimaPlatform.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL21;

			class FrameBufferGL21 : public AE::Graphics::Device::FrameBuffer
			{
			public:
				FrameBufferGL21(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc);
				~FrameBufferGL21();

				/***** Inherited from AE::Graphics::Device::PixelBuffer *****/
				void							blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition);
				void*							getData();
				void*							lock(AE::Graphics::LockType lockType);
				void							plot(const AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &position) {}
				void							plot32(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position) {}
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

				friend	AE::Graphics::Device::ContextGL21;

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