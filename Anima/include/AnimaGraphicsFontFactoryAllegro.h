#ifndef __AE_GRAPHICS_FONT_FACTORY_ALLEGRO__
#define __AE_GRAPHICS_FONT_FACTORY_ALLEGRO__

#include "AnimaGraphicsFontFactory.h"

#include "allegro5/allegro_ttf.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		class FontFace;

		class FontFactoryAllegro : public AE::Graphics::FontFactory
		{
		public:
			FontFactoryAllegro();
			~FontFactoryAllegro();

			FontFace* createFontFace(const std::string &fileName, AE::uint16 charWidth, AE::uint16 charHeight, AE::uint16 horizontalResolution, AE::uint16 verticalResolution, AE::uint fontOptions);
			void destroyFontFace(AE::Graphics::FontFace *fontFace);

		private:
			//FT_Library mLibraryFT;
		};
	}
}

#endif