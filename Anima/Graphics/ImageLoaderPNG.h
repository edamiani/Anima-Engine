#ifndef __AE_GRAPHICS_IMAGE_LOADER_PNG__
#define __AE_GRAPHICS_IMAGE_LOADER_PNG__

#include "Anima/Graphics/ImageLoader.h"

#include "Anima/Graphics/Enums.h"
#include "Anima/Types.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class Image;

		class ImageLoaderPng : public AE::Graphics::ImageLoader
		{
		public:
			ImageLoaderPng();
			~ImageLoaderPng();

			AE::Graphics::Image*	load(const std::string &fileName);
			bool					unload(AE::Graphics::Image *image);

		protected:
			AE::Graphics::ImageType mLoaderType;
		};
	}
}

#endif