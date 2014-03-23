#include "../include/AnimaGraphicsFontFactoryAllegro.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsFontFaceAllegro.h"

#include "allegro5/allegro_ttf.h"

namespace AE
{
	namespace Graphics
	{
		FontFactoryAllegro::FontFactoryAllegro() 
		{
			al_init_font_addon();
			al_init_ttf_addon();
		}

		FontFactoryAllegro::~FontFactoryAllegro() 
		{
			al_shutdown_ttf_addon();
			al_shutdown_font_addon();
		}

		FontFace* FontFactoryAllegro::createFontFace(const std::string &fileName, AE::uint16 charWidth, AE::uint16 charHeight, AE::uint16 horizontalResolution, AE::uint16 verticalResolution, AE::uint fontOptions)
		{
			ALLEGRO_FONT *allegroFace;

			int flags = 0;
			if(fontOptions & AE::Graphics::FO_MONOCHROME)
				flags = ALLEGRO_TTF_MONOCHROME;

			allegroFace = al_load_ttf_font(fileName.c_str(), charHeight, flags);
			
			if(allegroFace == 0)
				throw AE::Exception(AE::ET_FILE_NOT_FOUND, "Warning: Unable to load font");

			AE::Graphics::FontFace *newFace = new AE::Graphics::FontFaceAllegro(allegroFace);
			return newFace;
		}

		void FontFactoryAllegro::destroyFontFace(AE::Graphics::FontFace *fontFace)
		{
			delete fontFace;
		}
	}
}