#ifndef __AE_GRAPHICS_IMAGE_MANAGER_AE__
#define __AE_GRAPHICS_IMAGE_MANAGER_AE__

#include "AnimaGraphicsImageManager.h"

namespace AE
{
	namespace Graphics
	{
		class ImageManagerAE : public AE::Graphics::ImageManager
		{
		public:
			ImageManagerAE();
			~ImageManagerAE();

			/***** Inherited from AE::Graphics::ImageManager ******/

			AE::Graphics::Image*				createImage(std::string const &imageName, std::string const &fileName);
			void								destroyImage(std::string const &imageName);
			/* AE::Graphics::ImageFactory*		getImageFactory();
			*****/

			/***** Inherited from AE::Plugin *****/

			bool								install(AE::uint options);
			bool								uninstall();
			/*****/

		private:
			/***** Inherited from AE::Graphics::ImageManager

			static AE::Graphics::ImageManager	*mInstance;
			
			std::map<std::string, AE::Graphics::Image *>	
												mImages;
			AE::Graphics::ImageFactory *		mImageFactory;
			*****/
		};
	}
}

#endif