#include "../include/AnimaGraphicsFontManager.h"

#include "../include/AnimaGraphicsFontFactory.h"

AE::Graphics::Font::Manager* AE::Graphics::Font::Manager::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			Manager::Manager()
				: AE::Plugin(AE::PT_FONT_MANAGER)
			{
			}

			Manager::~Manager()
			{
			}

			AE::Graphics::Font::Face* Manager::createFontFace(const std::string &fontFaceName, const AE::Graphics::Font::FaceDesc &fontFaceDesc)
			{
				mFontFaces[fontFaceName] = mFontFactory->createFontFace(fontFaceDesc);

				return mFontFaces[fontFaceName];
			}
			
			void Manager::destroyFontFace(const std::string &fontFaceName)
			{
				mFontFactory->destroyFontFace(mFontFaces[fontFaceName]);
				
				mFontFaces.erase(fontFaceName);
			}
			
			void Manager::registerFontFile(const std::string &fileName, const std::string &registeredName) 
			{ 
				mFontFactory->registerFontFile(fileName, registeredName); 
			}
		}
	}
}