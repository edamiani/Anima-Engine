#include "../include/AnimaGraphicsSurfaceGL1_5.h"

#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaMathPoint2.h"
#include "../include/AnimaMathRectangle.h"
#include "../include/AnimaTypes.h"


namespace AE
{
	namespace Graphics
	{
		//SurfaceGL1_5::SurfaceGL1_5(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat)
		SurfaceGL1_5::SurfaceGL1_5(const AE::Graphics::SurfaceDesc &surfaceDesc)
			: AE::Graphics::Surface(surfaceDesc.dimensions), mData(0)
		{
			mAllocationType = surfaceDesc.allocationType;
			mPixelBufferType = surfaceDesc.pixelBufferType;

			mSurfaceFormat = surfaceDesc.surfaceFormat;

			AE::uint numberOfBytes = 0;

			switch(mSurfaceFormat)
			{
			case SF_A8R8G8B8:
				mPixelFormatGL = GL_BGRA;
				mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = 24;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;
				numberOfBytes = 4;
				break;
			case SF_X8R8G8B8:
				mPixelFormatGL = GL_BGRA;
				mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;
				numberOfBytes = 4;
				break;
			case SF_R8G8B8A8:
				mPixelFormatGL = GL_RGBA;
				mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = 24;
				mPixelFormat.redShift = 0;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 16;
				numberOfBytes = 4;
				break;
			case SF_R8G8B8X8:
				mPixelFormatGL = GL_ABGR_EXT;
				mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 0;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 16;
				numberOfBytes = 4;
				break;
			case SF_R8G8B8:
				mPixelFormatGL = GL_BGR;
				mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
				mPixelFormat.colorDepth = 24;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;
				numberOfBytes = 4;
				break;
			case SF_A1R5G5B5:
				mPixelFormatGL = GL_BGRA;
				mTypeGL = GL_UNSIGNED_SHORT_1_5_5_5_REV;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = 15;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;
				numberOfBytes = 2;
				break;
			case SF_X1R5G5B5:
				mPixelFormatGL = GL_BGRA;
				mTypeGL = GL_UNSIGNED_SHORT_1_5_5_5_REV;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;
				numberOfBytes = 2;
				break;
			case SF_R5G6B5:
				mPixelFormatGL = GL_BGR;
				mTypeGL = GL_UNSIGNED_SHORT_5_6_5_REV;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 11;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;
				numberOfBytes = 2;
				break;
			default:
				mPixelFormatGL = GL_BGR;
				mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
				mPixelFormat.colorDepth = 24;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;
				numberOfBytes = 4;
				break;
			}

			glGenTextures(1, &mTextureGL);
			glBindTexture(GL_TEXTURE_2D, mTextureGL);

			AE::Math::Point2<AE::uint> textureDimensions;

			// Loop to find the smaller power of 2 that encompasses the texture dimensions
			AE::int16 currentSize;

			for(AE::int16 i = 1; i < 16; i++)
			{
				currentSize = 1 << i;
				if(mDimensions.x < currentSize)
				{
					textureDimensions.x = currentSize; 
					break;
				}
			}

			for(AE::int16 i = 1; i < 16; i++)
			{
				currentSize = 1 << i;
				if(mDimensions.y < currentSize)
				{
					textureDimensions.y = currentSize;
					break;
				}
			}

			if(surfaceDesc.data != 0)
			{
				glTexSubImage2D(GL_TEXTURE_2D, /* mipmap level = */ 0, /* xoffset = */ 0, 
					/* yoffset = */ 0, surfaceDesc.dimensions.x, surfaceDesc.dimensions.y, 
					mPixelFormatGL, mTypeGL, surfaceDesc.data);
			}
			else
			{
				unsigned char *data = new unsigned char[textureDimensions.x * textureDimensions.y * numberOfBytes];
				memset(data, 0xFF, textureDimensions.x * textureDimensions.y * numberOfBytes);

				glTexSubImage2D(GL_TEXTURE_2D, /* mipmap level = */ 0, /* xoffset = */ 0, 
					/* yoffset = */ 0, surfaceDesc.dimensions.x, surfaceDesc.dimensions.y, 
					mPixelFormatGL, mTypeGL, data);
			}
		}

		SurfaceGL1_5::~SurfaceGL1_5()
		{
			if(mData)
				free(mData);
			else
				glDeleteTextures(1, &mTextureGL);
		}

		void SurfaceGL1_5::blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2<AE::uint> &sourceDimensions, const AE::Math::Point2<AE::int32> &destPosition)
		{
			void *source = sourceSurface->getData();

			glBindTexture(GL_TEXTURE_2D, mTextureGL);
			glTexSubImage2D(GL_TEXTURE_2D, /* mipmap level = */ 0, destPosition.x, 
				destPosition.y, sourceDimensions.x, sourceDimensions.y, 
				mPixelFormatGL, mTypeGL, source);
		}

		void SurfaceGL1_5::blit(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position)
		{
			//(*mBlitFunctor)(source, dimensions, position);
		}

		void SurfaceGL1_5::_blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position)
		{
			sourceSurface->lock(AE::Graphics::LT_READONLY);
				void *source = sourceSurface->getData();
				blit(source, dimensions, position);
			sourceSurface->unlock();
		}

		void SurfaceGL1_5::_blitAlpha(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position)
		{
			// ASSUMPTION: source data is always set from top to bottom.
			// This means the top-left pixel will be the first entry in the array.

			/*AE::Graphics::VerticalDirection verticalDirection = AE::Graphics::AxesConvention2d::getInstance()->getVerticalDirection();

			AE::Math::Rectangle clippedRegionSource;
			AE::Math::Rectangle clippedRegionDestination;

			AE::int32 widthCoordinate = position.x + dimensions.x;
			AE::int32 heightCoordinate = position.y + dimensions.y;

			AE::int32 trueWidth = mDimensions.x - 1;
			AE::int32 trueHeight = mDimensions.y - 1;

			if(position.x < 0)
			{
				if(widthCoordinate < 0)
				{
					clippedRegionSource.left = 0;
					clippedRegionSource.right = 0;

					clippedRegionDestination.left = 0;
					clippedRegionDestination.right = 0;
				}
				else
				{
					clippedRegionSource.left = -position.x;
					clippedRegionSource.right = dimensions.x;

					clippedRegionDestination.left = 0;
					clippedRegionDestination.right = dimensions.x + position.x;
				}
			}
			else if(position.x > mDimensions.x)
			{
				clippedRegionSource.left = 0;
				clippedRegionSource.right = 0;

				clippedRegionDestination.left = 0;
				clippedRegionDestination.right = 0;
			}
			else
			{
				if(widthCoordinate > mDimensions.x)
				{
					clippedRegionSource.left = 0;
					clippedRegionSource.right = mDimensions.x - position.x;

					clippedRegionDestination.left = position.x;
					clippedRegionDestination.right = mDimensions.x;
				}
				else
				{
					clippedRegionSource.left = 0;
					clippedRegionSource.right = dimensions.x;

					clippedRegionDestination.left = position.x;
					clippedRegionDestination.right = widthCoordinate;
				}
			}

			if(position.y < 0)
			{
				if(heightCoordinate < 0)
				{
					clippedRegionSource.top = 0;
					clippedRegionSource.bottom = 0;

					clippedRegionDestination.top = 0;
					clippedRegionDestination.bottom = 0;
				}
				else
				{
					//ok
					if(verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
					{
						clippedRegionSource.top = -position.y;
						clippedRegionSource.bottom = dimensions.y;

						clippedRegionDestination.top = mDimensions.y;
						clippedRegionDestination.bottom = mDimensions.y - heightCoordinate;
					}
					//ok
					else
					{
						clippedRegionSource.top = 0;
						clippedRegionSource.bottom = -position.y;

						clippedRegionDestination.top = heightCoordinate;
						clippedRegionDestination.bottom = 0;
					}
				}
			}
			//else if(position.y > trueHeight)
			else if(position.y > mDimensions.y)
			{
				clippedRegionSource.top = 0;
				clippedRegionSource.bottom = 0;

				clippedRegionDestination.top = 0;
				clippedRegionDestination.bottom = 0;
			}
			else
			{
				//if(heightCoordinate > trueHeight)
				if(heightCoordinate > mDimensions.y)
				{
					//ok
					if(verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
					{
						clippedRegionSource.top = 0;
						clippedRegionSource.bottom = mDimensions.y - position.y;

						clippedRegionDestination.top = mDimensions.y - position.y;
						clippedRegionDestination.bottom = 0;
					}
					//ok
					else
					{
						clippedRegionSource.top = mDimensions.y - position.y;
						clippedRegionSource.bottom = dimensions.y;

						clippedRegionDestination.top = mDimensions.y;
						clippedRegionDestination.bottom = position.y;
					}
				}
				else
				{
					//ok
					if(verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
					{
						clippedRegionSource.top = 0;
						clippedRegionSource.bottom = dimensions.y;

						clippedRegionDestination.top = mDimensions.y - position.y;
						clippedRegionDestination.bottom = clippedRegionDestination.top - dimensions.y;
					}
					//ok
					else
					{
						clippedRegionSource.top = 0;
						clippedRegionSource.bottom = dimensions.y;

						clippedRegionDestination.top = heightCoordinate;
						clippedRegionDestination.bottom = position.y;
					}
				}
			}

			AE::int32 rightOffset = dimensions.x - clippedRegionSource.right;

			if((clippedRegionSource.left != 0 || clippedRegionSource.right != 0) && (clippedRegionSource.top != 0 || clippedRegionSource.bottom != 0))
			{
				if(mPixelFormat.colorDepth == 16)
				{
					AE::uint16 *source16 = static_cast<AE::uint16 *>(source);
					source16 += clippedRegionSource.top * dimensions.x + clippedRegionSource.left;

					for(AE::int32 i = clippedRegionDestination.top; i > clippedRegionDestination.bottom; i--)
					{
						for(AE::int32 j = clippedRegionDestination.left; j < clippedRegionDestination.right; j++)
						{
							static_cast<AE::uint16 *>(mSurfaceGL)[i * mDimensions.x + j] = *source16;
							source16++;
						}
						source16 += rightOffset + clippedRegionSource.left;
					}
				}
				else
				{
					AE::uint32 *source32 = static_cast<AE::uint32 *>(source);
					source32 += clippedRegionSource.top * dimensions.x + clippedRegionSource.left;

					// OpenGL expects coordinates to be from bottom to top
					for(AE::int32 y = clippedRegionDestination.top - 1; y >= clippedRegionDestination.bottom; y--)
					{
						for(AE::int32 x = clippedRegionDestination.left; x < clippedRegionDestination.right; x++)
						{
							static_cast<AE::uint32 *>(mSurfaceGL)[y * mDimensions.x + x] = *source32;
							source32++;
						}
						source32 += rightOffset + clippedRegionSource.left;
					}
				}
			}*/
		}

		void SurfaceGL1_5::_blitNoAlpha(void *source, const AE::Math::Point2<AE::uint> &dimensions, const AE::Math::Point2<AE::int32> &position)
		{
			/*AE::uint16 trueHeight = mDimensions.y - 1;

			if(mPixelFormat.colorDepth == 16)
			{
				AE::uint16 *source16 = static_cast<AE::uint16 *>(source);
				for(AE::int32 i = trueHeight - position.y;
					i > trueHeight - (position.y + dimensions.y);
					i--)
				{
					for(AE::int32 j = position.x;
						j < position.x + dimensions.x;
						j++)
					{
						static_cast<AE::uint16 *>(mSurfaceGL)[i * mDimensions.x + j] = *source16;
						source16++;
					}
				}
			}
			else
			{
				AE::uint32 *source32 = static_cast<AE::uint32 *>(source);

				if(mUsesColorKey)
				{
					AE::uint32 colorKey = mColorKey.get32Bit();

					if(mIsOffScreen)
					{
						for(AE::uint32 i = static_cast<AE::uint32>(position.y);
							i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y);
							i++)
						{
							for(AE::int32 j = position.x;
								j < position.x + dimensions.x;
								j++)
							{
								if(*source32 != colorKey)
									static_cast<AE::uint32 *>(mSurfaceGL)[i * mDimensions.x + j] = *source32;
								else
									int x = 0;
								source32++;
							}
						}
					}
					else
					{
						for(AE::int32 i = trueHeight - position.y;
						i > trueHeight - (position.y + dimensions.y);
						i--)
						{
							for(AE::int32 j = position.x;
								j < position.x + dimensions.x;
								j++)
							{
								if(*source32 != colorKey)
									static_cast<AE::uint32 *>(mSurfaceGL)[i * mDimensions.x + j] = *source32;
								else
									int x = 0;
								source32++;
							}
						}
					}
				}
				else
				{
					if(mIsOffScreen)
					{
						for(AE::uint32 i = static_cast<AE::uint32>(position.y);
							i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y);
							i++)
						{
							for(AE::int32 j = position.x;
								j < position.x + dimensions.x;
								j++)
							{
								static_cast<AE::uint32 *>(mSurfaceGL)[i * mDimensions.x + j] = *source32;
								source32++;
							}
						}
					}
					else
					{
						for(AE::int32 i = trueHeight - position.y;
						i > trueHeight - (position.y + dimensions.y);
						i--)
						{
							for(AE::int32 j = position.x;
								j < position.x + dimensions.x;
								j++)
							{
								static_cast<AE::uint32 *>(mSurfaceGL)[i * mDimensions.x + j] = *source32;
								source32++;
							}
						}
					}
				}
			}*/
		}

		void SurfaceGL1_5::clear(const AE::Graphics::Color &backgroundColor)
		{
			/*lock(AE::Graphics::LT_DISCARD);

			for(AE::int32 i = 0; i < mDimensions.y; i++)
			{
				for(AE::int32 j = 0; j < mDimensions.x; j++)
				{
					plot(backgroundColor, AE::Math::Point2(j, i));
				}
			}

			unlock();*/
		}

		void* SurfaceGL1_5::getData()
		{
			glBindTexture(GL_TEXTURE_2D, mTextureGL);

			void *data = 0;
			glGetTexImage(GL_TEXTURE_2D, 0, mPixelFormatGL, mTypeGL, data);

			return data;
		}

		void SurfaceGL1_5::lock(AE::Graphics::LockType lockType)
		{
			/*switch(lockType)
			{
			case AE::Graphics::LT_DISCARD:
#ifdef AE_PLATFORM_WIN32
				::ZeroMemory(mSurfaceGL, mDimensions.x * mDimensions.y * (mPixelFormat.colorDepth / 8));
#elif defined(AE_PLATFORM_OSX)
                memset(mSurfaceGL, 0, mDimensions.x * mDimensions.y * (mPixelFormat.colorDepth / 8));
#endif
				break;
			}*/
		}

		void SurfaceGL1_5::plot(const AE::Graphics::Color &color, const AE::Math::Point2<AE::int32> &position)
		{
			/*if(mPixelFormat.colorDepth == 16)
			{
				AE::uint16 pixelColor = ((color.R >> (8 - (16 - mPixelFormat.redShift))) << mPixelFormat.redShift) +
										((color.G >> (8 - (mPixelFormat.redShift - mPixelFormat.greenShift))) << mPixelFormat.greenShift) +
										((color.B >> (8 - mPixelFormat.greenShift)) << mPixelFormat.blueShift);
				static_cast<AE::uint16 *>(mSurfaceGL)[(static_cast<AE::uint16>(position.y) * mDimensions.x) + static_cast<AE::uint16>(position.x)] = pixelColor;
			}
			else
			{
				AE::uint32 pixelColor = (color.R << mPixelFormat.redShift) +
										(color.G << mPixelFormat.greenShift) +
										(color.B << mPixelFormat.blueShift) +
										(255 << mPixelFormat.alphaShift);
				static_cast<AE::uint32 *>(mSurfaceGL)[(static_cast<AE::uint32>(position.y) * mDimensions.x) + static_cast<AE::uint32>(position.x)] = pixelColor;
			}*/
		}

		void SurfaceGL1_5::plot32(const AE::uint32 color, const AE::Math::Point2<AE::int32> &position)
		{
			//static_cast<AE::uint32 *>(mSurfaceGL)[(position.y * mDimensions.x) + position.x] = color;
		}

		void SurfaceGL1_5::unlock()
		{
			if(mPixelBufferType == AE::Graphics::Device::PBT_FRAME_BUFFER)
			{
				/*glViewport(0, 0, mWidth, mHeight);
				glMatrixMode(GL_PROJECTION);
				//glPushMatrix();
				glLoadIdentity();
				gluOrtho2(D0, mWidth, 0, mHeight);
				//glScalef(-1, -1, -1);
				//glTranslatef(0, 0.6, 0);
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				glWindowPos2i(0, 0);
				//glRasterPos2i(0, 0);*/

				////////////////////////////////////////////////////////////////
				//
				//  MUST BE REVISED!!!!!!!!!!!!!
				//
				////////////////////////////////////////////////////////////////


				glViewport(0, 0, mDimensions.x, mDimensions.y);

				// Reset the coordinate system before modifying
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				// Pseudo window coordinates
				gluOrtho2D(0, (GLfloat) mDimensions.x, 0, (GLfloat) mDimensions.y);

				//glScalef(1, -1, 1);
				//glTranslatef(0, -mHeight, 0);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				//glScalef(1, -1, 1);
				//glTranslatef(0, (GLfloat) -480, 0);
				//glScalef(1, -1, 1);*/

				glRasterPos2i(0, 0);
				//glDrawPixels(mDimensions.x, mDimensions.y, mPixelFormatGL, mTypeGL, mSurfaceGL);

				//glFlush();

				//glPopMatrix();
			}
		}
	}
}
