#include "../include/AnimaGraphicsImageAllegro.h"

namespace AE
{
	namespace Graphics
	{
		ImageAllegro::ImageAllegro(AE::Graphics::Surface *imageSurface)
			: Image(imageSurface)
		{
		}

		ImageAllegro::~ImageAllegro() 
		{ 
			/*if(mSurface)
				delete mSurface;*/
		}

		void* ImageAllegro::getData() 
		{ 
			/*assert(mTgaSpec._b_imageAndColorMapData._08_imageData);
			return static_cast<void *>(mTgaSpec._b_imageAndColorMapData._08_imageData);*/

			return 0;
		}

		const AE::Math::Point2 ImageAllegro::getDimensions()
		{
			return AE::Math::Point2(0, 0);
		}

		void ImageAllegro::load(const std::string &fileName)
		{
			
		}

		void ImageAllegro::save(const std::string &fileName)
		{
			
		}
	}
}