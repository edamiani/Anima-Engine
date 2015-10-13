#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_GL21__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_GL21__

#include "AnimaGraphicsDevicePixelBuffer.h"

#include "AnimaGraphicsDeviceGLHeaders.h"
#include "AnimaGraphicsDeviceManager.h"
#include "AnimaGraphicsDevicePixelBufferDesc.h"
#include "AnimaPlatform.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL21;
			class FrameBufferGL21;

			class PixelBufferGL21 : public AE::Graphics::Device::PixelBuffer
			{
			public:
				PixelBufferGL21(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc);
				~PixelBufferGL21();

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
				AE::uint						mBytesPerPixel;
				GLenum							mFormatGL;
				GLenum							mPixelFormatGL;
				GLuint							mPixelBufferGL;
				//AE::Math::Point2<AE::uint>		mTextureDimensions;
				GLenum							mTypeGL;

				friend							AE::Graphics::Device::ContextGL21;
				friend							AE::Graphics::Device::FrameBufferGL21;

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