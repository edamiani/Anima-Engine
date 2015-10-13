#include "../include/AnimaGraphicsImageManagerAE.h"

#include "../include/AnimaGraphicsImageFactoryAE.h"
#include "../include/AnimaGraphicsImageLoaderPng.h"
#include "../include/AnimaGraphicsImagePng.h"

namespace AE
{
	namespace Graphics
	{
		ImageManagerAE::ImageManagerAE()
		{
		}

		ImageManagerAE::~ImageManagerAE()
		{
		}

		AE::Graphics::Image* ImageManagerAE::createImage(std::string const &imageName, std::string const &fileName)
		{
			AE::Graphics::Image *newImage = mImageFactory->createImage(fileName);
			mImages[imageName] = newImage;

			return newImage;
		}

		void ImageManagerAE::destroyImage(std::string const &imageName)
		{
			delete mImages[imageName];
			mImages.erase(imageName);
		}

		bool ImageManagerAE::install(AE::uint options)
		{
			mImageFactory = new AE::Graphics::ImageFactoryAE();

			if(options & AE::Graphics::IT_PNG)
				mImageFactory->registerLoader(new AE::Graphics::ImageLoaderPng());

			mIsInstalled = true;

			return true;
		}

		bool ImageManagerAE::uninstall()
		{
			std::map<std::string, AE::Graphics::Image *>::iterator i;
			for(i = mImages.begin(); i != mImages.end(); i++)
				mImageFactory->destroyImage((*i).second);

			mImages.clear();

			if(mImageFactory)
			{
				delete mImageFactory;
				mImageFactory = 0;
			}

			return true;
		}
	}
}