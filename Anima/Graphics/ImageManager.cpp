#include "Anima/Graphics/ImageManager.h"

AE::Graphics::ImageManager* AE::Graphics::ImageManager::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		ImageManager::ImageManager() 
			: AE::Plugin(AE::PT_IMAGE_MANAGER) 
		{ 
		}

		ImageManager::~ImageManager() 
		{
		}
	}
}