#ifndef __AE_GRAPHICS_DEVICE_COLOR_BUFFER__
#define __AE_GRAPHICS_DEVICE_COLOR_BUFFER__

#include "Anima/Graphics/Device/ColorBufferDesc.h"

#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ColorBuffer
			{
			public:
				ColorBuffer(AE::Graphics::Device::ColorBufferDesc const &colorBufferDesc) : 
					mColorFormat(colorBufferDesc.colorFormat), mData(colorBufferDesc.data),
					mDimensions(colorBufferDesc.dimensions), /*mRowOrder(colorBufferDesc.rowOrder),*/
					mUsage(colorBufferDesc.usage) {}

				virtual ~ColorBuffer() 
				{
					if(mData)
						delete mData;
				}

				virtual void*		getData() = 0;
				AE::Math::Point2<AE::int32>	getDimensions() { return mDimensions; }
				/*AE::Graphics::RowOrder
									getRowOrder() { return mRowOrder; }*/

				/*struct ColorStructure
				{
					AE::uint8	bitDepth;
					AE::int8	redShift;
					AE::int8	greenShift;
					AE::int8	blueShift;
					AE::int8	alphaShift;
				};*/

			protected:
				AE::Graphics::ColorFormat			mColorFormat;
				//ColorStructure						mColorStructure;
				void								*mData;
				AE::Math::Point2<AE::int32>			mDimensions;
				//AE::Graphics::RowOrder				mRowOrder;
				AE::Graphics::Device::BufferUsage	mUsage;
			};
		}
	}
}

#endif