#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_GL1_5__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_GL1_5__

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
			class ContextGL1_5;
			class FrameBufferGL1_5;

			class PixelBufferGL1_5 : public AE::Graphics::Device::PixelBuffer
			{
			public:
				PixelBufferGL1_5(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc);
				~PixelBufferGL1_5();

				void							blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition);
				void*							getData();
				void							lock(AE::Graphics::LockType lockType) {}
				void							plot(const AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &position) {}
				void							plot32(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position) {}
				void							unlock() {}

				/***** Inherited from AE::Graphics::ColorBuffer
				AE::Graphics::ColorFormat		getColorFormat();
				void*							getData();
				AE::Math::Point2&				getDimensions();
				AE::Math::Point2&				getRowOrder();
				*****/

			private:
				GLenum							mPixelFormatGL;
				AE::Math::Point2<AE::uint>		mTextureDimensions;
				GLuint							mTextureGL;
				GLenum							mTypeGL;

				friend							AE::Graphics::Device::ContextGL1_5;
				friend							AE::Graphics::Device::FrameBufferGL1_5;

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