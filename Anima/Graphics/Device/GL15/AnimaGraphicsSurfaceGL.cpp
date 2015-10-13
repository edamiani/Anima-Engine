#include "../include/AnimaGraphicsSurfaceGL.h"

namespace AE
{
	namespace Graphics
	{
		SurfaceGL::SurfaceGL(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat)
			: mWidth(width), mHeight(height)
		{
			mIsOffScreen = true;

			mSurfaceFormat = surfaceFormat;

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

				mBlitFunctor = new BlitFunctorGL(this, &AE::Graphics::SurfaceGL::_blitAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorGL(this, &AE::Graphics::SurfaceGL::_blit);
				break;
			case SF_X8R8G8B8:
				mPixelFormatGL = GL_BGRA;
				mTypeGL = GL_UNSIGNED_INT_8_8_8_8_REV;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorGL(this, &AE::Graphics::SurfaceGL::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorGL(this, &AE::Graphics::SurfaceGL::_blit);
				break;
			case SF_A1R5G5B5:
				mPixelFormatGL = GL_BGRA;
				mTypeGL = GL_UNSIGNED_SHORT_1_5_5_5_REV;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = 15;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorGL(this, &AE::Graphics::SurfaceGL::_blitAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorGL(this, &AE::Graphics::SurfaceGL::_blit);
				break;
			case SF_X1R5G5B5:
				mPixelFormatGL = GL_BGRA;
				mTypeGL = GL_UNSIGNED_SHORT_1_5_5_5_REV;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorGL(this, &AE::Graphics::SurfaceGL::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorGL(this, &AE::Graphics::SurfaceGL::_blit);
				break;
			case SF_R5G6B5:
				mPixelFormatGL = GL_BGR;
				mTypeGL = GL_UNSIGNED_SHORT_5_6_5_REV;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 11;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorGL(this, &AE::Graphics::SurfaceGL::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorGL(this, &AE::Graphics::SurfaceGL::_blit);
				break;
			}

			mSurfaceGL = static_cast<GLbyte *>(malloc(mWidth * mHeight * (mPixelFormat.colorDepth / 8)));
		    assert(mSurfaceGL != NULL);
		}

		SurfaceGL::~SurfaceGL() 
		{
			free(mSurfaceGL);
		}

		void SurfaceGL::blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			(*mBlitFromSurfaceFunctor)(sourceSurface, dimensions, position);
		}

		void SurfaceGL::blit(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			(*mBlitFunctor)(source, dimensions, position);
		}

		void SurfaceGL::_blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			sourceSurface->lock(AE::Graphics::LT_READONLY);
				void *source = sourceSurface->getData();
				blit(source, dimensions, position);
			sourceSurface->unlock();
		}

		void SurfaceGL::_blitAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			AE::uint16 trueHeight = mHeight - 1;

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
						static_cast<AE::uint16 *>(mSurfaceGL)[i * mWidth + j] = *source16;
						source16++;
					}
				}
			}
			else
			{
				AE::uint32 *source32 = static_cast<AE::uint32 *>(source);
				for(AE::int32 i = trueHeight - position.y; 
					i > trueHeight - (position.y + dimensions.y);
					i--)
				{
					for(AE::int32 j = position.x; 
						j < position.x + dimensions.x; 
						j++)
					{
						static_cast<AE::uint32 *>(mSurfaceGL)[i * mWidth + j] = *source32;
						source32++;
					}
				}
			}
		}

		void SurfaceGL::_blitNoAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			AE::uint16 trueHeight = mHeight - 1;

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
						static_cast<AE::uint16 *>(mSurfaceGL)[i * mWidth + j] = *source16;
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
									static_cast<AE::uint32 *>(mSurfaceGL)[i * mWidth + j] = *source32;
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
									static_cast<AE::uint32 *>(mSurfaceGL)[i * mWidth + j] = *source32;
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
								static_cast<AE::uint32 *>(mSurfaceGL)[i * mWidth + j] = *source32;
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
								static_cast<AE::uint32 *>(mSurfaceGL)[i * mWidth + j] = *source32;
								source32++;
							}
						}
					}
				}
			}
		}

		void SurfaceGL::clear(const AE::Graphics::Color &backgroundColor)
		{
			lock(AE::Graphics::LT_DISCARD);

			for(AE::uint i = 0; i < mHeight; i++)
			{
				for(AE::uint j = 0; j < mWidth; j++)
				{
					plot(backgroundColor, AE::Math::Point2(j, i));
				}
			}

			unlock();
		}

		void* SurfaceGL::getData()
		{ 
			return mSurfaceGL;
		}
		
		AE::Math::Point2 SurfaceGL::getDimensions() 
		{ 
			return AE::Math::Point2(mWidth, mHeight); 
		}
		
		void SurfaceGL::lock(AE::Graphics::LockType lockType) 
		{
			switch(lockType)
			{
			case AE::Graphics::LT_DISCARD:
#ifdef AE_PLATFORM_WIN32
				::ZeroMemory(mSurfaceGL, mWidth * mHeight * (mPixelFormat.colorDepth / 8));
#endif
				break;
			}
		}

		void SurfaceGL::plot(const AE::Graphics::Color &color, const AE::Math::Point2 &position) 
		{
			if(mPixelFormat.colorDepth == 16)
			{
				AE::uint16 pixelColor = ((color.R >> (8 - (16 - mPixelFormat.redShift))) << mPixelFormat.redShift) + 
										((color.G >> (8 - (mPixelFormat.redShift - mPixelFormat.greenShift))) << mPixelFormat.greenShift) + 
										((color.B >> (8 - mPixelFormat.greenShift)) << mPixelFormat.blueShift);
				static_cast<AE::uint16 *>(mSurfaceGL)[(static_cast<AE::uint16>(position.y) * mWidth) + static_cast<AE::uint16>(position.x)] = pixelColor;
			}
			else
			{
				AE::uint32 pixelColor = (color.R << mPixelFormat.redShift) + 
										(color.G << mPixelFormat.greenShift) + 
										(color.B << mPixelFormat.blueShift) + 
										(255 << mPixelFormat.alphaShift); 
				static_cast<AE::uint32 *>(mSurfaceGL)[(static_cast<AE::uint32>(position.y) * mWidth) + static_cast<AE::uint32>(position.x)] = pixelColor;
			}
		}

		void SurfaceGL::plot32(const AE::uint32 color, const AE::Math::Point2 &position) 
		{
			static_cast<AE::uint32 *>(mSurfaceGL)[(position.y * mWidth) + position.x] = color;
		}
		
		void SurfaceGL::unlock() 
		{
			if(!mIsOffScreen)
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


				glViewport(0, 0, mWidth, mHeight);

				// Reset the coordinate system before modifying

				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();

				// Pseudo window coordinates
				gluOrtho2D(0, (GLfloat) mWidth, 0, (GLfloat) mHeight);

				//glScalef(1, -1, 1);
				//glTranslatef(0, -mHeight, 0);

				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();

				//glScalef(1, -1, 1);
				//glTranslatef(0, (GLfloat) -480, 0);
				//glScalef(1, -1, 1);

				glRasterPos2i(0, 0);
				glDrawPixels(mWidth, mHeight, mPixelFormatGL, mTypeGL, mSurfaceGL);

				//glPopMatrix();
			}
		}
	}
}