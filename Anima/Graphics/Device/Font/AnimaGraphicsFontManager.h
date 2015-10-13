#ifndef __AE_GRAPHICS_FONT_MANAGER__
#define __AE_GRAPHICS_FONT_MANAGER__

#include "AnimaPlugin.h"

#include "AnimaGraphicsFontFaceDesc.h"

#include <map>
#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			class Face;
			class Factory;

			class Manager : public AE::Plugin
			{
			public:
				Manager();
				virtual ~Manager();

				static AE::Graphics::Font::Manager* getInstance() { assert(mInstance != 0); return mInstance; }

				AE::Graphics::Font::Face*			createFontFace(const std::string &fontFaceName, const AE::Graphics::Font::FaceDesc &fontFaceDesc);
				void								destroyFontFace(const std::string &fontFaceName);
				AE::Graphics::Font::Factory*		getFontFactory() { return mFontFactory; }
				void								registerFontFile(const std::string &fileName, const std::string &registeredName);

			protected:
				static AE::Graphics::Font::Manager	*mInstance;
				
				std::map<std::string, AE::Graphics::Font::Face *>	
													mFontFaces;
				AE::Graphics::Font::Factory			*mFontFactory;
			};
		}
	}
}

#endif