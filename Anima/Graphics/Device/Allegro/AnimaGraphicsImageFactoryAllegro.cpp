#include "../include/AnimaGraphicsImageFactoryAllegro.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsImageAllegro.h"
#include "../include/AnimaGraphicsSurfaceAllegro.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		ImageFactoryAllegro::ImageFactoryAllegro() 
		{
			al_init_image_addon();
		}

		ImageFactoryAllegro::~ImageFactoryAllegro() 
		{
			al_shutdown_image_addon();
		}

		AE::Graphics::Image* ImageFactoryAllegro::createImage(const std::string &fileName, AE::Graphics::AllocationType allocationType)
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

			allegroBitmap = al_load_bitmap(fileName.c_str());
			
			if(allegroBitmap == 0)
				throw AE::Exception(AE::ET_FILE_NOT_FOUND, "Warning: Unable to load image");

			AE::Graphics::Surface *newSurface = new AE::Graphics::SurfaceAllegro(allegroBitmap);
			AE::Graphics::Image *newImage = new AE::Graphics::ImageAllegro(newSurface);

			return newImage;
		}
		
		void ImageFactoryAllegro::destroyImage(AE::Graphics::Image *image)
		{
			ALLEGRO_BITMAP *bitmap = static_cast<AE::Graphics::SurfaceAllegro *>(image->getSurface())->_getAllegroBitmap();
			al_destroy_bitmap(bitmap);

			delete image->getSurface();
			delete image;
		}
	}
}