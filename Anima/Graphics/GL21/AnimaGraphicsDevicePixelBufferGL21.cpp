#include "../include/AnimaGraphicsDevicePixelBufferGL21.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaGraphicsImage.h"
#include "../include/AnimaMathVector2.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			PixelBufferGL21::PixelBufferGL21(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc) :
				AE::Graphics::Device::PixelBuffer(pixelBufferDesc)
			{
				AE::uint numberOfChannels = 0;

				mColorFormat = pixelBufferDesc.colorFormatConversion;

				switch(mColorFormat)
				{
				case CF_A8R8G8B8:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					mBytesPerPixel = 4;
					numberOfChannels = 4;
					break;
				case CF_X8R8G8B8:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					mBytesPerPixel = 4;
					numberOfChannels = 3;
					break;
				case CF_R8G8B8A8:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					mBytesPerPixel = 4;
					numberOfChannels = 4;
					break;
				case CF_R8G8B8X8:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					mBytesPerPixel = 4;
					numberOfChannels = 3;
					break;
				case CF_R8G8B8:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_BYTE;
					mBytesPerPixel = 3;
					break;
				case CF_A1R5G5B5:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_SHORT_5_5_5_1;
					mBytesPerPixel = 2;
					break;
				case CF_X1R5G5B5:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_SHORT_5_5_5_1;
					mBytesPerPixel = 2;
					numberOfChannels = 3;
					break;
				case CF_R5G6B5:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_SHORT_5_6_5_REV;
					mBytesPerPixel = 2;
					numberOfChannels = 3;
					break;
				default:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					mBytesPerPixel = 4;
					numberOfChannels = 4;
					break;
				}

				/*switch(pixelBufferDesc.colorBufferDesc.colorFormat)
				{
				case CF_A8R8G8B8:
				case CF_X8R8G8B8:
					mFormatGL = GL_ABGR_EXT;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					break;
				case CF_R8G8B8A8:
				case CF_R8G8B8X8:
					mFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					break;
				case CF_A1R5G5B5:
				case CF_X1R5G5B5:
					mFormatGL = GL_ABGR_EXT;
					mTypeGL = GL_UNSIGNED_SHORT_5_5_5_1;
					break;
				case CF_R5G6B5:
					mFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_SHORT_5_6_5_REV;
					break;
				case CF_R8G8B8:
					mFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_BYTE;
					break;
				default:
					throw AE::Exception(AE::ET_NOT_FOUND, "AE::Graphics::Device::PixelBufferGL21::PixelBufferGL21(): Image doesn't have a supported color format");
				}*/

				AE::Math::Point2<AE::uint> imageDimensions = pixelBufferDesc.colorBufferDesc.dimensions;

				glGenBuffers(1, &mPixelBufferGL);

				if(pixelBufferDesc.colorBufferDesc.data != 0)
				{
					GLenum usage;
					switch(pixelBufferDesc.usage)
					{
					case AE::Graphics::Device::BU_DYNAMIC_COPY:		usage = GL_DYNAMIC_COPY; break;
					case AE::Graphics::Device::BU_DYNAMIC_READ:		usage = GL_DYNAMIC_READ; break;
					case AE::Graphics::Device::BU_DYNAMIC_WRITE:	usage = GL_DYNAMIC_DRAW; break;
					case AE::Graphics::Device::BU_STATIC_COPY:		usage = GL_STATIC_COPY; break;
					case AE::Graphics::Device::BU_STATIC_READ:		usage = GL_STATIC_READ; break;
					case AE::Graphics::Device::BU_STATIC_WRITE:		usage = GL_STATIC_DRAW; break;
					case AE::Graphics::Device::BU_STREAM_COPY:		usage = GL_STREAM_COPY; break;
					case AE::Graphics::Device::BU_STREAM_READ:		usage = GL_STREAM_READ; break;
					case AE::Graphics::Device::BU_STREAM_WRITE:		usage = GL_STREAM_DRAW; break;
					}

					glPixelStorei(GL_UNPACK_ALIGNMENT, mBytesPerPixel);

					glGenBuffers(1, &mPixelBufferGL);
					glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPixelBufferGL);
					glBufferData(GL_PIXEL_UNPACK_BUFFER, mBytesPerPixel * imageDimensions.x * imageDimensions.y, pixelBufferDesc.colorBufferDesc.data, usage);
					
					assert(glGetError() == 0);

					if(mAllocationType = AE::Graphics::AT_MANAGED_MEMORY)
						memcpy(mData, pixelBufferDesc.colorBufferDesc.data, 
							imageDimensions.x * imageDimensions.y * mBytesPerPixel);
					else
						mData = 0;
				}
			}

			PixelBufferGL21::~PixelBufferGL21()
			{
				glDeleteBuffers(1, &mPixelBufferGL);
			}

			void PixelBufferGL21::blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition)
			{
				assert(srcDimensions.x >= srcOffset.x && 
					   srcDimensions.y >= srcOffset.y);

				void *pixels = source->getData();

				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPixelBufferGL);

				AE::int32 y;
				AE::Math::Point2<AE::uint> dimensions(srcDimensions.x - srcOffset.x, srcDimensions.y - srcOffset.y);

				if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_BOTTOM_TO_TOP)
					y = mDimensions.y - destPosition.y - dimensions.y;
				else
					y = destPosition.y;

				glBufferSubData(GL_PIXEL_UNPACK_BUFFER,  
								destPosition.x * destPosition.y * mBytesPerPixel, // offset
								srcDimensions.x * srcDimensions.y * mBytesPerPixel, // size
								pixels);

				GLenum error = glGetError();
				assert(error == 0);
			}

			void* PixelBufferGL21::getData()
			{
				return mData;
			}

			void* PixelBufferGL21::lock(AE::Graphics::LockType lockType)
			{
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPixelBufferGL);
				return glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_WRITE);
			}

			void PixelBufferGL21::unlock()
			{
				glBindBuffer(GL_PIXEL_UNPACK_BUFFER, mPixelBufferGL);
				glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
			}
		}
	}
}