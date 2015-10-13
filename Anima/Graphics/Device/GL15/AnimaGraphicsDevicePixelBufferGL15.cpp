#include "AnimaGraphicsDevicePixelBufferGL15.h"

#include "Anima/AnimaException.h"
#include "Anima/Graphics/AnimaGraphicsAxesConvention2d.h"
#include "Anima/Graphics/AnimaGraphicsImage.h"
#include "Anima/Math/AnimaMathVector2.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			PixelBufferGL15::PixelBufferGL15(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc) :
				AE::Graphics::Device::PixelBuffer(pixelBufferDesc)
			{
				AE::uint numberOfBytes = 0;
				AE::uint numberOfChannels = 0;

				mColorFormat = pixelBufferDesc.colorFormatConversion;

				switch(mColorFormat)
				{
				case CF_A8R8G8B8:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					numberOfBytes = 4;
					numberOfChannels = 4;
					break;
				case CF_X8R8G8B8:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					numberOfBytes = 4;
					numberOfChannels = 3;
					break;
				case CF_R8G8B8A8:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					numberOfBytes = 4;
					numberOfChannels = 4;
					break;
				case CF_R8G8B8X8:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					numberOfBytes = 4;
					numberOfChannels = 3;
					break;
				case CF_R8G8B8:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_BYTE;
					numberOfBytes = 3;
					break;
				case CF_A1R5G5B5:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_SHORT_5_5_5_1;
					numberOfBytes = 2;
					break;
				case CF_X1R5G5B5:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_SHORT_5_5_5_1;
					numberOfBytes = 2;
					numberOfChannels = 3;
					break;
				case CF_R5G6B5:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_SHORT_5_6_5_REV;
					numberOfBytes = 2;
					numberOfChannels = 3;
					break;
				default:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					numberOfBytes = 4;
					numberOfChannels = 4;
					break;
				}

				// Loop to find the smaller power of 2 that encompasses texture dimensions
				AE::uint currentSize;

				for(AE::uint i = 1; i < 16; i++)
				{
					currentSize = 1 << i;
					if(mDimensions.x < currentSize)
					{
						mTextureDimensions.x = currentSize; 
						break;
					}
				}

				for(AE::uint i = 1; i < 16; i++)
				{
					currentSize = 1 << i;
					if(mDimensions.y < currentSize)
					{
						mTextureDimensions.y = currentSize;
						break;
					}
				}
				
				glGenTextures(1, &mTextureGL);
				glBindTexture(GL_TEXTURE_2D, mTextureGL);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

				glTexImage2D(GL_TEXTURE_2D, /* mipmap = */ 0, /* internalFormat = */ numberOfChannels, 
					mTextureDimensions.x, mTextureDimensions.y,
					/* border = */ 0, mPixelFormatGL, mTypeGL, 0);

				GLenum error = glGetError();
				assert(error == 0);

				GLenum imageFormatGL;
				GLenum imageTypeGL;

				switch(pixelBufferDesc.colorBufferDesc.colorFormat)
				{
				case CF_A8R8G8B8:
				case CF_X8R8G8B8:
					imageFormatGL = GL_ABGR_EXT;
					imageTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					break;
				case CF_R8G8B8A8:
				case CF_R8G8B8X8:
					imageFormatGL = GL_RGBA;
					imageTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					break;
				case CF_A1R5G5B5:
				case CF_X1R5G5B5:
					imageFormatGL = GL_ABGR_EXT;
					imageTypeGL = GL_UNSIGNED_SHORT_5_5_5_1;
					break;
				case CF_R5G6B5:
					imageFormatGL = GL_RGB;
					imageTypeGL = GL_UNSIGNED_SHORT_5_6_5_REV;
					break;
				case CF_R8G8B8:
					imageFormatGL = GL_RGB;
					imageTypeGL = GL_UNSIGNED_BYTE;
					break;
				default:
					throw AE::Exception(AE::ET_NOT_FOUND, "AE::Graphics::Device::PixelBufferGL15::PixelBufferGL15(): Image doesn't have a supported color format");
				}

				AE::Math::Point2<AE::uint> imageDimensions = pixelBufferDesc.colorBufferDesc.dimensions;

				if(pixelBufferDesc.colorBufferDesc.data != 0)
				{
					// Create a copy of data to ensure ownership
					mData = malloc(imageDimensions.x * imageDimensions.y * numberOfBytes);
					memcpy(mData, pixelBufferDesc.colorBufferDesc.data, imageDimensions.x * imageDimensions.y * numberOfBytes);

					glTexSubImage2D(GL_TEXTURE_2D, /* mipmap level = */ 0, /* xoffset = */ 0, /* yoffset = */ 0, 
						imageDimensions.x, imageDimensions.y, 
						imageFormatGL, imageTypeGL, pixelBufferDesc.colorBufferDesc.data);

					error = glGetError();
					assert(error == 0);

					if(mAllocationType = AE::Graphics::AT_MANAGED_MEMORY)
						memcpy(mData, pixelBufferDesc.colorBufferDesc.data, 
							imageDimensions.x * imageDimensions.y * numberOfBytes);
				}

				
				/*if(pixelBufferDesc.allocationType == AE::Graphics::AT_VIDEO_MEMORY)
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

					glPixelStorei(GL_UNPACK_ALIGNMENT, numberOfBytes);

					GLenum error = glGetError();

					glGenBuffers(1, &mPixelBufferGL);
					error = glGetError();
					glBindBuffer(GL_PIXEL_UNPACK_BUFFER_EXT, mPixelBufferGL);
					error = glGetError();
					glBufferData(GL_PIXEL_UNPACK_BUFFER_ARB, numberOfBytes * pixelBufferDesc.dimensions.x * pixelBufferDesc.dimensions.y, pixelBufferDesc.data, usage);
					error = glGetError();
				}*/
			}

			PixelBufferGL15::~PixelBufferGL15()
			{
				//glDeleteBuffers(1, &mPixelBufferGL);
				glDeleteTextures(1, &mTextureGL);
			}

			void PixelBufferGL15::blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition)
			{
				assert(srcDimensions.x >= srcOffset.x && 
					   srcDimensions.y >= srcOffset.y);

				void *pixels = source->getData();

				glBindTexture(GL_TEXTURE_2D, mTextureGL);

				AE::int32 y;
				AE::Math::Point2<AE::uint> dimensions(srcDimensions.x - srcOffset.x, srcDimensions.y - srcOffset.y);

				if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_BOTTOM_TO_TOP)
					y = mDimensions.y - destPosition.y - dimensions.y;
				else
					y = destPosition.y;

				glTexSubImage2D(GL_TEXTURE_2D, 0, 
								destPosition.x, y, 
								dimensions.x, dimensions.y, 
								static_cast<AE::Graphics::Device::PixelBufferGL15 *>(source)->mPixelFormatGL, 
								static_cast<AE::Graphics::Device::PixelBufferGL15 *>(source)->mTypeGL, 
								pixels);

				GLenum error = glGetError();
				assert(error == 0);
			}

			void* PixelBufferGL15::getData()
			{
				if(!mData)
				{
					glBindTexture(GL_TEXTURE_2D, mTextureGL);

					GLint width, height;
					glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
					glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);
					//glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPONENTS, &numComponents);

					AE::uint numBytes;
					switch(mTypeGL)
					{
					case GL_BYTE:
					case GL_UNSIGNED_BYTE:
					case GL_UNSIGNED_BYTE_3_3_2: 
					case GL_UNSIGNED_BYTE_2_3_3_REV:
						numBytes = sizeof(GLbyte);
						break;
					case GL_SHORT:
					case GL_UNSIGNED_SHORT:
					case GL_UNSIGNED_SHORT_5_6_5: 
					case GL_UNSIGNED_SHORT_5_6_5_REV: 
					case GL_UNSIGNED_SHORT_4_4_4_4: 
					case GL_UNSIGNED_SHORT_4_4_4_4_REV: 
					case GL_UNSIGNED_SHORT_5_5_5_1: 
					case GL_UNSIGNED_SHORT_1_5_5_5_REV:
						numBytes = sizeof(GLshort);
						break;
					case GL_INT:
					case GL_UNSIGNED_INT: 
					case GL_UNSIGNED_INT_8_8_8_8: 
					case GL_UNSIGNED_INT_8_8_8_8_REV: 
					case GL_UNSIGNED_INT_10_10_10_2:
					case GL_UNSIGNED_INT_2_10_10_10_REV:
						numBytes = sizeof(GLint);
						break;
					case GL_FLOAT:
						numBytes = sizeof(GLfloat);
						break;
					}

					void *pixels = malloc(width * height * numBytes);
					glGetTexImage(GL_TEXTURE_2D, 0, mPixelFormatGL, mTypeGL, pixels);

					return pixels;
				}

				return mData;
			}
		}
	}
}