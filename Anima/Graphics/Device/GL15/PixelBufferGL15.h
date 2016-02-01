#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_GL15__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_GL15__

#include "Anima/Graphics/Device/PixelBuffer.h"

#include "Anima/Platform.h"
#include "Anima/Graphics/Device/GL15/GLHeaders.h"
#include "Anima/Graphics/Device/Manager.h"
#include "Anima/Graphics/Device/PixelBufferDesc.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL15;
			class FrameBufferGL15;

			class PixelBufferGL15 : public AE::Graphics::Device::PixelBuffer
			{
			public:
				PixelBufferGL15(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc);
				~PixelBufferGL15();

				void							blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition);
				void*							getData();
				void*							lock(AE::Graphics::LockType lockType) { return 0; }
				void							plot(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position) {}
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

				friend							AE::Graphics::Device::ContextGL15;
				friend							AE::Graphics::Device::FrameBufferGL15;

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