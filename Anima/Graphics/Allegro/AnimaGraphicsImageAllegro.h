#ifndef __ANIMA_GRAPHICS_IMAGE_ALLEGRO__
#define __ANIMA_GRAPHICS_IMAGE_ALLEGRO__

#include "AnimaGraphicsImage.h"

namespace AE
{
	namespace Graphics
	{
		class ImageAllegro : public AE::Graphics::Image
		{
		public:
			ImageAllegro(AE::Graphics::Surface *imageSurface);
			~ImageAllegro();

			void* getData();
			const AE::Math::Point2 getDimensions();
			void load(const std::string &fileName);
			void save(const std::string &fileName);

		protected:
			
		};
	}
}

#endif