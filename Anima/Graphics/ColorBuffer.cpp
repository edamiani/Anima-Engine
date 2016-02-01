#include "ColorBuffer.h"

namespace AE
{
	namespace Graphics
	{
		ColorBuffer::ColorBuffer(AE::Graphics::ColorBufferDesc const &colorBufferDesc) : 
			mBufferType(AE::Graphics::BT_COLOR_BUFFER),
			mColorFormat(colorBufferDesc.colorFormat), 
			mData(colorBufferDesc.data),
			mDimensions(colorBufferDesc.dimensions) 
		{
			AE::uint numberOfBytes;

			switch(colorBufferDesc.colorFormat)
			{
			case CF_A8R8G8B8:
			case CF_X8R8G8B8:
			case CF_R8G8B8A8:
			case CF_R8G8B8X8:
				numberOfBytes = 4;
				break;
			case CF_R8G8B8:
				numberOfBytes = 3;
				break;
			case CF_A1R5G5B5:
			case CF_X1R5G5B5:
			case CF_R5G6B5:
				numberOfBytes = 2;
				break;
			default:
				numberOfBytes = 4;
				break;
			}

			if(colorBufferDesc.data)
			{
				//mData = malloc(numberOfBytes * mDimensions.x * mDimensions.y);
				mData = new AE::byte[numberOfBytes * mDimensions.x * mDimensions.y];
				memcpy(mData, colorBufferDesc.data, numberOfBytes * mDimensions.x * mDimensions.y);
			}
		}

		ColorBuffer::~ColorBuffer() 
		{
			if(mData)
				//free(mData);
				delete[] mData;
		}
	}
}