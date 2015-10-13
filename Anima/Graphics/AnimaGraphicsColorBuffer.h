#ifndef __AE_GRAPHICS_COLOR_BUFFER__
#define __AE_GRAPHICS_COLOR_BUFFER__

#include "AnimaGraphicsColorBufferDesc.h"
#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class FrameBuffer;
		}

		class ColorBuffer
		{
		public:
			ColorBuffer(AE::Graphics::ColorBufferDesc const &colorBufferDesc);
			virtual ~ColorBuffer();

			AE::Graphics::BufferType	getBufferType() { return mBufferType; }
			AE::Graphics::ColorFormat	getColorFormat() { return mColorFormat; }
			virtual void*				getData() { return mData; }
			AE::Math::Point2<AE::uint>	getDimensions() { return mDimensions; }

		protected:
			AE::Graphics::BufferType	mBufferType;
			AE::Graphics::ColorFormat	mColorFormat;
			void						*mData;
			AE::Math::Point2<AE::uint>	mDimensions;
		};
	}
}

#endif