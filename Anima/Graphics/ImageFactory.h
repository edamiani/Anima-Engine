#ifndef __AE_GRAPHICS_IMAGE_FACTORY__
#define __AE_GRAPHICS_IMAGE_FACTORY__

#include "Anima/Graphics/Enums.h"
#include "Anima/Graphics/ImageDesc.h"
#include "Anima/Types.h"

#include <map>
#include <string>

namespace AE
{
	namespace Graphics
	{
		class Image;
		class ImageLoader;

		class ImageFactory
		{
		public:
			ImageFactory();
			virtual ~ImageFactory();

			virtual AE::Graphics::Image*	createImage(const std::string &fileName) = 0;
			virtual bool					destroyImage(AE::Graphics::Image *image) = 0;
			virtual void					registerLoader(AE::Graphics::ImageLoader *imageLoader) = 0;

		protected:
			std::map<AE::Graphics::ImageType, AE::Graphics::ImageLoader *> mLoaders;
		};
	}
}

#endif