#include "../include/AnimaGraphicsSurfaceDX10.h"

namespace AE
{
	namespace Graphics
	{
		SurfaceDX10::SurfaceDX10(const AE::Math::Point2 &dimensions, IDXGISurface *DXGISurface)
			: AE::Graphics::Surface(dimensions), mDXGISurface(DXGISurface)
		{
			DXGI_SURFACE_DESC surfaceDesc;
			mDXGISurface->GetDesc(&surfaceDesc);
			
			// NB: DirectX uses the format ARGB
			// NB 2: A -1 shift value means it doesn't exist
			switch(surfaceDesc.Format)
			{
			case DXGI_FORMAT_B8G8R8A8_UNORM:
				mSurfaceFormat = SF_A8R8G8B8;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = 24;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorDX10(this, &AE::Graphics::SurfaceDX10::_blitAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorDX10(this, &AE::Graphics::SurfaceDX10::_blit);
				break;
			/*case D3DFMT_X8R8G8B8:
				mSurfaceFormat = SF_X8R8G8B8;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blit);
				break;*/
			/*case D3DFMT_A1R5G5B5:
				mSurfaceFormat = SF_A1R5G5B5;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = 15;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blitAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blit);
				break;*/
			/*case D3DFMT_X1R5G5B5:
				mSurfaceFormat = SF_X1R5G5B5;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blit);
				break;*/
			/*case D3DFMT_R5G6B5:
				mSurfaceFormat = SF_R5G6B5;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 11;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorDX9(this, &AE::Graphics::SurfaceDX9::_blit);
				break;*/
			}
		}

		SurfaceDX10::~SurfaceDX10() 
		{
			mDXGISurface->Release();
			mDXGISurface = NULL;
		}

		void SurfaceDX10::blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			(*mBlitFromSurfaceFunctor)(sourceSurface, dimensions, position);
		}

		void SurfaceDX10::blit(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			(*mBlitFunctor)(source, dimensions, position);
		}

		void SurfaceDX10::_blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			/*sourceSurface->lock(AE::Graphics::LT_READONLY);
			void *source = sourceSurface->getData();
			if(mPixelFormat.colorDepth == 16)
			{
				AE::uint16 strideInBytes = mLockedRect.Pitch / 2;
				AE::uint16 *source16 = static_cast<AE::uint16 *>(source);
				for(AE::uint32 i = static_cast<AE::uint32>(position.y); 
					i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y); 
					i++)
				{
					for(AE::uint32 j = static_cast<AE::uint32>(position.x); 
						j < static_cast<AE::uint32>(position.x) + static_cast<AE::uint32>(dimensions.x); 
						j++)
					{
						static_cast<AE::uint16 *>(mLockedRect.pBits)[i * mPitch + j] = *source16;
						source16++;
					}
				}
			}
			else
			{
				AE::uint32 *source32 = static_cast<AE::uint32 *>(source);
				for(AE::uint32 i = static_cast<AE::uint32>(position.y); 
					i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y); 
					i++)
				{
					for(AE::uint32 j = static_cast<AE::uint32>(position.x); 
						j < static_cast<AE::uint32>(position.x) + static_cast<AE::uint32>(dimensions.x); 
						j++)
					{
						static_cast<AE::uint32 *>(mLockedRect.pBits)[i * mPitch + j] = *source32;
						source32++;
					}
				}
			}
			sourceSurface->unlock();*/
		}

		void SurfaceDX10::_blitAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			/*if(mPixelFormat.colorDepth == 16)
			{
				AE::uint16 strideInBytes = mLockedRect.Pitch / 2;
				for(AE::uint32 i = static_cast<AE::uint32>(position.y); 
					i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y); 
					i++)
				{
					for(AE::uint32 j = static_cast<AE::uint32>(position.x); 
						j < static_cast<AE::uint32>(position.x) + static_cast<AE::uint32>(dimensions.x); 
						j++)
					{
						static_cast<AE::uint16 *>(mLockedRect.pBits)[i * strideInBytes + j] = *static_cast<AE::uint16 *>(source);
					}
				}
			}
			else
			{
				AE::uint32 *dest = static_cast<AE::uint32 *>(mLockedRect.pBits);
				AE::uint32 *src = static_cast<AE::uint32 *>(source);
				dest += static_cast<AE::uint32>(position.y) * mPitch + static_cast<AE::uint32>(position.x);

				AE::uint32 *nextRow = dest + mPitch;
				AE::uint32 countDownY = static_cast<AE::uint32>(dimensions.y);
				void *colorSrc = src;
				void *colorDest = dest;
				AE::uint8 *colorSrc2 = static_cast<AE::uint8 *>(colorSrc);
				AE::uint8 *colorDest2 = static_cast<AE::uint8 *>(colorDest);
				AE::uint8 redS, redD, greenS, greenD, blueS, blueD; 
				float alphaS, invAlphaS;
				do
				{
					AE::uint32 countDownX = static_cast<AE::uint32>(dimensions.x);
					do
					{
						//Blue?
						blueS = (*src & 0x000000ff);
						blueD = (*dest & 0x000000ff);
						// Green?
						greenS = (*src & 0x0000ff00) >> 8;
						greenD = (*dest & 0x0000ff00) >> 8;
						// Red?
						redS = (*src & 0x00ff0000) >> 16;
						redD = (*dest & 0x00ff0000) >> 16;
						// Alpha?
						alphaS = ((*src & 0xff000000) >> 24) / 255.0f;
						invAlphaS = 1 - alphaS;

						AE::uint32 destColor =  (static_cast<AE::uint32>(blueS * alphaS + blueD * invAlphaS) +
												(static_cast<AE::uint32>(greenS * alphaS + greenD * invAlphaS) << 8) +
												(static_cast<AE::uint32>(redS * alphaS + redD * invAlphaS) << 16));

						*dest++ = destColor;
						*src++;

						//*dest++ = *src++;
					}
					while(--countDownX);

					dest = nextRow;
					nextRow += mPitch;
				}
				while(--countDownY);
			}*/
		}

		void SurfaceDX10::_blitNoAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			/*if(mPixelFormat.colorDepth == 16)
			{
				AE::uint16 strideInBytes = mLockedRect.Pitch / 2;
				AE::uint16 *source16 = static_cast<AE::uint16 *>(source);
				for(AE::uint32 i = static_cast<AE::uint32>(position.y); 
					i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y); 
					i++)
				{
					for(AE::uint32 j = static_cast<AE::uint32>(position.x); 
						j < static_cast<AE::uint32>(position.x) + static_cast<AE::uint32>(dimensions.x); 
						j++)
					{
						static_cast<AE::uint16 *>(mLockedRect.pBits)[i * mPitch + j] = *source16;
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

					for(AE::uint32 i = static_cast<AE::uint32>(position.y); 
						i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y); 
						i++)
					{
						for(AE::uint32 j = static_cast<AE::uint32>(position.x); 
							j < static_cast<AE::uint32>(position.x) + static_cast<AE::uint32>(dimensions.x); 
							j++)
						{
							if(*source32 != colorKey)
								static_cast<AE::uint32 *>(mLockedRect.pBits)[i * mPitch + j] = *source32;
							source32++;
						}
					}
				}
				else
				{
					for(AE::uint32 i = static_cast<AE::uint32>(position.y); 
						i < static_cast<AE::uint32>(position.y) + static_cast<AE::uint32>(dimensions.y); 
						i++)
					{
						for(AE::uint32 j = static_cast<AE::uint32>(position.x); 
							j < static_cast<AE::uint32>(position.x) + static_cast<AE::uint32>(dimensions.x); 
							j++)
						{
							static_cast<AE::uint32 *>(mLockedRect.pBits)[i * mPitch + j] = *source32;
							source32++;
						}
					}
				}
			}*/
		}

		void SurfaceDX10::clear(const AE::Graphics::Color &backgroundColor)
		{
			/*lock(AE::Graphics::LT_DISCARD);

			for(AE::uint i = 0; i < mSurfaceDesc.Height; i++)
			{
				for(AE::uint j = 0; j < mSurfaceDesc.Width; j++)
				{
					plot(backgroundColor, AE::Math::Point2(j, i));
				}
			}

			unlock();*/
		}

		void* SurfaceDX10::getData()
		{
			//return mLockedRect.pBits;
			return 0;
		}

		AE::Math::Point2 SurfaceDX10::getDimensions()
		{
			//return AE::Math::Point2(mSurfaceDesc.Width, mSurfaceDesc.Height);
			return AE::Math::Point2(0, 0);
		}

		void SurfaceDX10::lock(AE::Graphics::LockType lockType)
		{
			/*DWORD d3dLock;
			switch(lockType)
			{
			case AE::Graphics::LT_DISCARD:
				d3dLock = D3DLOCK_DISCARD;
				break;
			case AE::Graphics::LT_NO_DIRTY_UPDATE:
				d3dLock = D3DLOCK_NO_DIRTY_UPDATE;
				break;
			case AE::Graphics::LT_NOSYSLOCK:
				d3dLock = D3DLOCK_NOSYSLOCK;
				break;
			case AE::Graphics::LT_READONLY:
				d3dLock = D3DLOCK_READONLY;
				break;
			}
			HRESULT result = mSurfaceDX9->LockRect(&mLockedRect, NULL, d3dLock);
			assert(result == D3D_OK);
			mPitch = mLockedRect.Pitch / 4;*/
		}

		void SurfaceDX10::plot(const AE::Graphics::Color &color, const AE::Math::Point2 &position) 
		{
			/*if(mPixelFormat.colorDepth == 16)
			{
				AE::uint16 pixelColor = ((color.R >> (8 - (16 - mPixelFormat.redShift))) << mPixelFormat.redShift) + 
										((color.G >> (8 - (mPixelFormat.redShift - mPixelFormat.greenShift))) << mPixelFormat.greenShift) + 
										((color.B >> (8 - mPixelFormat.greenShift)) << mPixelFormat.blueShift);
				static_cast<AE::uint16 *>(mLockedRect.pBits)[(static_cast<AE::uint32>(position.y) * (mLockedRect.Pitch / 2)) + static_cast<AE::uint32>(position.x)] = pixelColor;
			}
			else
			{
				AE::uint32 pixelColor =	(color.A << mPixelFormat.alphaShift) +
										(color.R << mPixelFormat.redShift) + 
										(color.G << mPixelFormat.greenShift) + 
										(color.B << mPixelFormat.blueShift);
				static_cast<AE::uint32 *>(mLockedRect.pBits)[(static_cast<AE::uint32>(position.y) * (mLockedRect.Pitch / 4)) + static_cast<AE::uint32>(position.x)] = pixelColor;
			}*/
		}

		void SurfaceDX10::plot32(const AE::uint32 color, const AE::Math::Point2 &position) 
		{
			//static_cast<AE::uint32 *>(mLockedRect.pBits)[(static_cast<AE::uint32>(position.y) * (mLockedRect.Pitch / 4)) + static_cast<AE::uint32>(position.x)] = color;
		}

		void SurfaceDX10::unlock()
		{
			//mSurfaceDX9->UnlockRect();
		}
	}
}