#ifndef __AE_GRAPHICS_IMAGE_FACTORY_AE__
#define __AE_GRAPHICS_IMAGE_FACTORY_AE__

#include "AnimaGraphicsImageFactory.h"

namespace AE
{
	namespace Graphics
	{
		class ImageFactoryAE : public AE::Graphics::ImageFactory
		{
		public:
			ImageFactoryAE();
			~ImageFactoryAE();

			AE::Graphics::Image*	createImage(const std::string &fileName);
			bool					destroyImage(AE::Graphics::Image *image);
			void					registerLoader(AE::Graphics::ImageLoader *imageLoader);

		private:
		};
	}
}

#endif