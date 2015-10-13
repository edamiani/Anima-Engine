#include "AnimaGraphicsDeviceFrameBufferGL15.h"
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
			FrameBufferGL15::FrameBufferGL15(const AE::Graphics::Device::PixelBufferDesc &pixelBufferDesc) :
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
			}

			FrameBufferGL15::~FrameBufferGL15()
			{
			}

			void FrameBufferGL15::blitFrom(AE::Graphics::ColorBuffer *source, AE::Math::Point2<AE::uint> srcOffset, AE::Math::Point2<AE::uint> srcDimensions, AE::Math::Point2<AE::int32> const &destPosition)
			{
				if(source->getBufferType() == AE::Graphics::BT_PIXEL_BUFFER)
				{
					AE::Graphics::Device::PixelBufferGL15 *pbSource = static_cast<AE::Graphics::Device::PixelBufferGL15 *>(source);
					glBindTexture(GL_TEXTURE_2D, pbSource->mTextureGL);

					AE::Math::Point2<AE::uint> dimensions(srcDimensions.x - srcOffset.x, srcDimensions.y - srcOffset.y);
					AE::Math::Point2<AE::int32> position(destPosition.x, 0);
					AE::Math::Rectangle drawingArea(srcDimensions.y - srcOffset.y, srcOffset.x, srcOffset.y, srcDimensions.x - srcOffset.x);

					if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
					{
						position.y = mDimensions.y - destPosition.y - dimensions.y;
						//rectangle.top = srcRectangle.top;
						//rectangle.bottom = srcRectangle.bottom;
					}
					else
					{
						position.y = destPosition.y;
						//rectangle.top = srcRectangle.bottom;
						//rectangle.bottom = srcRectangle.top;
					}

					glBegin(GL_TRIANGLE_STRIP);
						// v1
						glTexCoord2f((float)drawingArea.right / pbSource->mTextureDimensions.x, (float)drawingArea.bottom / pbSource->mTextureDimensions.y);
						glVertex2d(position.x + dimensions.x, position.y + dimensions.y);
						// v2
						glTexCoord2f((float)drawingArea.left / pbSource->mTextureDimensions.x, (float)drawingArea.bottom / pbSource->mTextureDimensions.y);
						glVertex2d(position.x, position.y + dimensions.y);
						// v3
						glTexCoord2f((float)drawingArea.right / pbSource->mTextureDimensions.x, (float)drawingArea.top / pbSource->mTextureDimensions.y);
						glVertex2d(position.x + dimensions.x, position.y);
						// v4
						glTexCoord2f((float)drawingArea.left / pbSource->mTextureDimensions.x, (float)drawingArea.top / pbSource->mTextureDimensions.y);
						glVertex2d(position.x, position.y);
					glEnd();
				}
				else if(source->getBufferType() == AE::Graphics::BT_COLOR_BUFFER)
				{
					AE::Math::Point2<AE::uint> dimensions(srcDimensions.x - srcOffset.x, srcDimensions.y - srcOffset.y);
					AE::Math::Point2<AE::int32> position(destPosition.x, 0);

					if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
						position.y = mDimensions.y - destPosition.y - dimensions.y;
					else
						position.y = destPosition.y;

					glPixelZoom(1, -1);
					glWindowPos2i(position.x, position.y + source->getDimensions().y);
					GLenum error = glGetError();
					assert(glGetError() == 0);

					glDrawPixels(dimensions.x,
						dimensions.y,
						mPixelFormatGL,
						mTypeGL,
						source->getData()); // When using a PBO, this parameter sets the OFFSET from the PBO data store
					error = glGetError();
					assert(glGetError() == 0);

					glPixelZoom(1, 1);
				}
			}

			void* FrameBufferGL15::getData()
			{
				if(!mData)
				{
					

					//return pixels;
				}

				return mData;
			}

			void* FrameBufferGL15::lock(AE::Graphics::LockType lockType)
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

			void FrameBufferGL15::unlock()
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