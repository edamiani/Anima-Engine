#ifndef __AE_GRAPHICS_FONT_FACTORY_FT__
#define __AE_GRAPHICS_FONT_FACTORY_FT__

#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsFontFactory.h"

#include "ft2build.h"
#include FT_FREETYPE_H 

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			class Face;

			class FactoryFT : public AE::Graphics::Font::Factory
			{
			public:
				FactoryFT() 
				{
				}

				~FactoryFT() {}

				AE::Graphics::Font::Face* createFontFace(const AE::Graphics::Font::FaceDesc &fontFaceDesc);
				void destroyFontFace(AE::Graphics::Font::Face *fontFace);

			private:
			};
		}
	}
}

#endif