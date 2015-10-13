#include "../include/AnimaGraphicsSurfaceFactoryAllegro.h"
#include "../include/AnimaGraphicsSurfaceAllegro.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		SurfaceFactoryAllegro::SurfaceFactoryAllegro() 
		{
		}

		SurfaceFactoryAllegro::~SurfaceFactoryAllegro() 
		{
		}

		AE::Graphics::Surface* SurfaceFactoryAllegro::createSurface(const AE::Math::Point2 &dimensions, AE::Graphics::AllocationType allocationType)
		{
			ALLEGRO_BITMAP *allegroBitmap;
			switch(allocationType)
			{
			case AE::Graphics::AT_SYSTEM_MEMORY:
				al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
				break;
			case AE::Graphics::AT_PRIMARY_VIDEO:
			case AE::Graphics::AT_SECONDARY_VIDEO:
				al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
				break;
			}

			allegroBitmap = al_create_bitmap(dimensions.x, dimensions.y);
			AE::Graphics::Surface *newSurface = new AE::Graphics::SurfaceAllegro(allegroBitmap);
			
			return newSurface;
		}
		
		void SurfaceFactoryAllegro::destroySurface(AE::Graphics::Surface *surface)
		{
			ALLEGRO_BITMAP *bitmap = static_cast<AE::Graphics::SurfaceAllegro *>(surface)->_getAllegroBitmap();
			al_destroy_bitmap(bitmap);

			delete surface;
		}
	}
}