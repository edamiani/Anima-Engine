#include "../include/AnimaGraphicsSurfaceAllegro.h"

namespace AE
{
	namespace Graphics
	{
		SurfaceAllegro::SurfaceAllegro(ALLEGRO_BITMAP *allegroBitmap)
			: mAllegroBitmap(allegroBitmap)
		{
			int pixelFormat = al_get_bitmap_format(mAllegroBitmap);
			
			switch(pixelFormat)
			{
			case ALLEGRO_PIXEL_FORMAT_ARGB_8888:
				mSurfaceFormat = SF_A8R8G8B8;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = 24;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blitAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blit);
				break;
			case ALLEGRO_PIXEL_FORMAT_XRGB_8888:
				mSurfaceFormat = SF_X8R8G8B8;
				mPixelFormat.colorDepth = 32;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 16;
				mPixelFormat.greenShift = 8;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blit);
				break;
			case ALLEGRO_PIXEL_FORMAT_ARGB_1555:
				mSurfaceFormat = SF_A1R5G5B5;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = 15;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blitAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blit);
				break;
			/*case ALLEGRO_PIXEL_FORMAT_XRGB_1555:
				mSurfaceFormat = SF_X1R5G5B5;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 10;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blit);
				break;*/
			case ALLEGRO_PIXEL_FORMAT_RGB_565:
				mSurfaceFormat = SF_R5G6B5;
				mPixelFormat.colorDepth = 16;
				mPixelFormat.alphaShift = -1;
				mPixelFormat.redShift = 11;
				mPixelFormat.greenShift = 5;
				mPixelFormat.blueShift = 0;

				mBlitFunctor = new BlitFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blitNoAlpha);
				mBlitFromSurfaceFunctor = new BlitFromSurfaceFunctorAllegro(this, &AE::Graphics::SurfaceAllegro::_blit);
				break;
			}
		}

		SurfaceAllegro::~SurfaceAllegro() 
		{
		}

		void SurfaceAllegro::blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			(*mBlitFromSurfaceFunctor)(sourceSurface, dimensions, position);
		}

		void SurfaceAllegro::blit(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			(*mBlitFunctor)(source, dimensions, position);
		}

		void SurfaceAllegro::_blit(AE::Graphics::Surface *sourceSurface, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
			al_set_target_bitmap(mAllegroBitmap);
			al_draw_bitmap_region(static_cast<AE::Graphics::SurfaceAllegro *>(sourceSurface)->_getAllegroBitmap(), 0, 0, dimensions.x, dimensions.y, position.x, position.y, 0);
		}

		void SurfaceAllegro::_blitAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
		}

		void SurfaceAllegro::_blitNoAlpha(void *source, const AE::Math::Point2 &dimensions, const AE::Math::Point2 &position)
		{
		}

		void SurfaceAllegro::clear(const AE::Graphics::Color &backgroundColor)
		{
			al_set_target_bitmap(mAllegroBitmap);
			al_clear_to_color(al_map_rgb(backgroundColor.R, backgroundColor.G, backgroundColor.B));
		}

		void* SurfaceAllegro::getData()
		{
			return 0;
		}

		AE::Math::Point2 SurfaceAllegro::getDimensions()
		{
			return AE::Math::Point2(al_get_bitmap_width(mAllegroBitmap), al_get_bitmap_height(mAllegroBitmap));
		}

		void SurfaceAllegro::lock(AE::Graphics::LockType lockType)
		{
			AE::uint allegroLockType;
			switch(lockType)
			{
			case AE::Graphics::LT_READONLY:
				allegroLockType = ALLEGRO_LOCK_READONLY;
				break;
			case AE::Graphics::LT_WRITEONLY:
				allegroLockType = ALLEGRO_LOCK_WRITEONLY;
				break;
			case AE::Graphics::LT_READWRITE:
			default:
				allegroLockType = ALLEGRO_LOCK_READWRITE;
				break;
			}

			ALLEGRO_LOCKED_REGION *lockedRegion = al_lock_bitmap(mAllegroBitmap, al_get_bitmap_format(mAllegroBitmap), allegroLockType);
			assert(lockedRegion);
		}

		void SurfaceAllegro::plot(const AE::Graphics::Color &color, const AE::Math::Point2 &position) 
		{
			al_put_pixel(position.x, position.y, al_map_rgb(color.R, color.G, color.B));
		}

		void SurfaceAllegro::plot32(const AE::uint32 color, const AE::Math::Point2 &position) 
		{
		}

		void SurfaceAllegro::unlock()
		{
			al_unlock_bitmap(mAllegroBitmap);
		}
	}
}