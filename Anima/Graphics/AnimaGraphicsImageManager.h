#ifndef __AE_GRAPHICS_IMAGE_MANAGER__
#define __AE_GRAPHICS_IMAGE_MANAGER__

#include "../AnimaPlugin.h"

#include "AnimaGraphicsEnums.h"

#include <map>

namespace AE
{
	namespace Graphics
	{
		class Image;
		class ImageFactory;

		class ImageManager : public AE::Plugin
		{
		public:
			ImageManager();
			virtual ~ImageManager();

			static AE::Graphics::ImageManager* getInstance() { assert(mInstance != 0); return mInstance; }

			virtual AE::Graphics::Image*		createImage(std::string const &imageName, std::string const &fileName) = 0;
			virtual void						destroyImage(std::string const &imageName) = 0;
			AE::Graphics::ImageFactory*			getImageFactory() { return mImageFactory; }

		protected:
			static AE::Graphics::ImageManager	*mInstance;
			
			std::map<std::string, AE::Graphics::Image *>	
												mImages;
			AE::Graphics::ImageFactory *		mImageFactory;
		};
	}
}

#endif