#include "../include/AnimaGraphicsImageFactoryAE.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsImage.h"
#include "../include/AnimaGraphicsImageLoader.h"
#include "../include/AnimaGraphicsImageRaw.h"

namespace AE
{
	namespace Graphics
	{
		ImageFactoryAE::ImageFactoryAE()
		{
		}

		ImageFactoryAE::~ImageFactoryAE()
		{
			std::map<AE::Graphics::ImageType, AE::Graphics::ImageLoader *>::iterator i;
			for(i = mLoaders.begin(); i != mLoaders.end(); i++)
				delete (*i).second;

			mLoaders.clear();
		}

		AE::Graphics::Image* ImageFactoryAE::createImage(const std::string &fileName)
		{
			size_t found;
			found = fileName.find_last_of(".");
			std::string extension = fileName.substr(found + 1);

			AE::Graphics::Image *image = 0;

			// TODO: transform to lowercase before verification
			if(extension == "png")
				image = mLoaders[AE::Graphics::IT_PNG]->load(fileName);
			else
				throw AE::Exception(AE::ET_NOT_SUPPORTED, "AE::Graphics::ImageFactoryAE::createImage(): extension not supported by this factory.");

			return image;
		}

		bool ImageFactoryAE::destroyImage(AE::Graphics::Image *image)
		{
			// FIXME: unsafe container access
			bool result = mLoaders[image->getImageType()]->unload(image);

			return result;
		}

		void ImageFactoryAE::registerLoader(AE::Graphics::ImageLoader *imageLoader)
		{
			mLoaders[imageLoader->getType()] = imageLoader;
		}
	}
}