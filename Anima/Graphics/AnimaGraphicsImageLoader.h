#ifndef __AE_GRAPHICS_IMAGE_LOADER__
#define __AE_GRAPHICS_IMAGE_LOADER__

#include "AnimaGraphicsEnums.h"
#include "../AnimaTypes.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class Image;

		class ImageLoader
		{
		public:
			ImageLoader(AE::Graphics::ImageType loaderType) : mLoaderType(loaderType) {}
			virtual ~ImageLoader() {}

			AE::Graphics::ImageType			getType() { return mLoaderType; }
			virtual AE::Graphics::Image*	load(const std::string &fileName) = 0;
			virtual bool					unload(AE::Graphics::Image *image) = 0;

		protected:
			AE::Graphics::ImageType mLoaderType;
		};
	}
}

#endif