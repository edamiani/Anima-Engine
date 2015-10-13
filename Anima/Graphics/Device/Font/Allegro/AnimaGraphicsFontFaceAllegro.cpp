#include "../include/AnimaGraphicsFontFaceAllegro.h"

#include "allegro5/allegro_ttf.h"
#include "allegro5/utf8.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		FontFaceAllegro::FontFaceAllegro(ALLEGRO_FONT *fontFace)
			: mFontFace(fontFace)
		{
		}

		FontFaceAllegro::~FontFaceAllegro() 
		{
			al_destroy_font(mFontFace);
		}

		void FontFaceAllegro::write(const std::string &text, const AE::Math::Point2 &position, const AE::Graphics::Color &color)
		{
			ALLEGRO_COLOR allegroColor = al_map_rgba(color.R, color.G, color.B, color.A);
			//ALLEGRO_USTR *allegroString = al_ustr_new(text.c_str());
			ALLEGRO_USTR *allegroString = al_ustr_new(text.c_str());
			//int size = al_ustr_size(allegroString);
			//al_draw_ustr(mFontFace, allegroColor, position.x, position.y, 0, allegroString);
			al_draw_ustr(mFontFace, allegroColor, position.x, position.y, 0, allegroString);
			al_ustr_free(allegroString);
		}
	}
}