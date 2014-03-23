#include "../include/AnimaGraphicsDeviceFrameBufferGL21.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaGraphicsDevicePixelBufferGL21.h"
#include "../include/AnimaGraphicsImage.h"
#include "../include/AnimaMathVector2.h"

#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			FrameBufferGL21::FrameBufferGL21(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc) :
				AE::Graphics::Device::FrameBuffer(pixelBufferDesc)
			{
				AE::uint numberOfBytes = 0;
				AE::uint numberOfChannels = 0;

				mColorFormat = pixelBufferDesc.colorFormatConversion;

				switch(mColorFormat)
				{
				case CF_X8R8G8B8:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					break;
				case CF_R8G8B8:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_BYTE;
					break;
				case CF_A1R5G5B5:
				case CF_X1R5G5B5:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_SHORT_5_5_5_1;
					break;
				case CF_R5G6B5:
					mPixelFormatGL = GL_RGB;
					mTypeGL = GL_UNSIGNED_SHORT_5_6_5_REV;
					break;
				case CF_A8R8G8B8:
				case CF_R8G8B8A8:
				case CF_R8G8B8X8:
				default:
					mPixelFormatGL = GL_RGBA;
					mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
					break;
				}

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
				}
			}

			FrameBufferGL21::~FrameBufferGL21()
			{
			}

			void FrameBufferGL21::blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition)
			{
				if(source->getBufferType() == AE::Graphics::BT_PIXEL_BUFFER)
				{
					AE::Graphics::Device::PixelBufferGL21 *pbSource = static_cast<AE::Graphics::Device::PixelBufferGL21 *>(source);
					glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pbSource->mPixelBufferGL);
					GLenum error = glGetError();

					AE::Math::Point2<AE::uint> dimensions(srcDimensions.x - srcOffset.x, srcDimensions.y - srcOffset.y);
					AE::Math::Point2<AE::int32> position(destPosition.x, 0);

					if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
						position.y = mDimensions.y - destPosition.y - dimensions.y;
					else
						position.y = destPosition.y;

					glPixelZoom(1, -1);
					glWindowPos2i(position.x, position.y + source->getDimensions().y);
					error = glGetError();

					glDrawPixels(dimensions.x,
						dimensions.y,
						pbSource->mPixelFormatGL,
						pbSource->mTypeGL,
						BUFFER_OFFSET(0)); // When using a PBO, this parameter sets the OFFSET from the PBO data store
					error = glGetError();

					glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
					error = glGetError();
					assert(glGetError() == 0);
					glPixelZoom(1, 1);
				}
			}

			void* FrameBufferGL21::getData()
			{
				if(!mData)
				{
					

					//return pixels;
				}

				return mData;
			}

			void* FrameBufferGL21::lock(AE::Graphics::LockType lockType)
			{
				glDisable(GL_DEPTH_TEST);

				glMatrixMode(GL_PROJECTION);
				glPushMatrix();	
				glLoadIdentity();

				gluOrtho2D(0, mDimensions.x, 0, mDimensions.y);

				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();	
				glLoadIdentity();

				return 0;
			}

			void FrameBufferGL21::unlock()
			{
				glMatrixMode(GL_PROJECTION);
				glPopMatrix();

				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();

				glEnable(GL_DEPTH_TEST);
			}
		}
	}
}