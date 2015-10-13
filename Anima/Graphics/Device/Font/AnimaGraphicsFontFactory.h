#ifndef __AE_GRAPHICS_FONT_FACTORY__
#define __AE_GRAPHICS_FONT_FACTORY__

#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsFontFaceDesc.h"
#include "AnimaTypes.h"

#include <map>
#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			class Face;

			class Factory
			{
			public:
				Factory();
				virtual ~Factory();

				virtual AE::Graphics::Font::Face* createFontFace(const AE::Graphics::Font::FaceDesc &fontFaceDesc) = 0;
				virtual void destroyFontFace(AE::Graphics::Font::Face *fontFace) = 0;
				void registerFontFile(const std::string &fileName, const std::string &registeredName);
				void unregisterFontFile(const std::string &registeredName);

			protected:
				std::map<std::string, std::string> mRegisteredFonts;
			};
		}
	}
}

#endif