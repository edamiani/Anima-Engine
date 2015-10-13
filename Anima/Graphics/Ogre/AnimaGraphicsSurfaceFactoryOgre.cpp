#include "../include/AnimaGraphicsSurfaceFactoryOgre.h"

#include "../include/AnimaGraphicsSurfaceOgre.h"

#include "Ogre.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		SurfaceFactoryOgre::SurfaceFactoryOgre() 
		{
		}

		SurfaceFactoryOgre::~SurfaceFactoryOgre() 
		{
		}

		AE::Graphics::Surface* SurfaceFactoryOgre::createSurface(const AE::Math::Point2 &dimensions, AE::Graphics::AllocationType allocationType)
		{
			/*ALLEGRO_BITMAP *allegroBitmap;
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
			
			return newSurface;*/
			return 0;
		}
		
		void SurfaceFactoryOgre::destroySurface(AE::Graphics::Surface *surface)
		{
			/*ALLEGRO_BITMAP *bitmap = static_cast<AE::Graphics::SurfaceAllegro *>(surface)->_getAllegroBitmap();
			al_destroy_bitmap(bitmap);

			delete surface;*/
		}
	}
}