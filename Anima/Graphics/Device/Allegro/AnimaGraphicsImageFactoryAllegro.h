#ifndef __AE_GRAPHICS_IMAGE_FACTORY_ALLEGRO__
#define __AE_GRAPHICS_IMAGE_FACTORY_ALLEGRO__

#include "AnimaGraphicsImageFactory.h"

#include <cassert>
#include <string>

namespace AE
{
	namespace Graphics
	{
		class Image;

		class ImageFactoryAllegro : public AE::Graphics::ImageFactory
		{
		public:
			ImageFactoryAllegro();
			~ImageFactoryAllegro();

			AE::Graphics::Image* createImage(const std::string &fileName, AE::Graphics::AllocationType allocationType);
			void destroyImage(AE::Graphics::Image *image);

		private:
			//FT_Library mLibraryFT;
		};
	}
}

#endif