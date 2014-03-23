#include "../include/AnimaGraphicsSurfaceFactoryDX11.h"
#include "../include/AnimaGraphicsSurfaceDX11.h"

#include "d3d11.h"
#include "dxgi.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		SurfaceFactoryDX11::SurfaceFactoryDX11() 
		{
		}

		SurfaceFactoryDX11::~SurfaceFactoryDX11() 
		{
		}

		AE::Graphics::Surface* SurfaceFactoryDX11::createSurface(const AE::Graphics::SurfaceDesc &surfaceDesc)
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
		
		void SurfaceFactoryDX11::destroySurface(AE::Graphics::Surface *surface)
		{
			/*ALLEGRO_BITMAP *bitmap = static_cast<AE::Graphics::SurfaceAllegro *>(surface)->_getAllegroBitmap();
			al_destroy_bitmap(bitmap);

			delete surface;*/
		}
	}
}