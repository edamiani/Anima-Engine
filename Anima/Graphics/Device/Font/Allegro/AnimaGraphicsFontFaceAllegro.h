#ifndef __AE_GRAPHICS_FONT_FACE_ALLEGRO__
#define __AE_GRAPHICS_FONT_FACE_ALLEGRO__

#include "AnimaGraphicsFontFace.h"

#include "allegro5/allegro_ttf.h"

namespace AE
{
	namespace Graphics
	{
		class FontFaceAllegro : public AE::Graphics::FontFace
		{
		public:
			FontFaceAllegro(ALLEGRO_FONT *fontFace);
			virtual ~FontFaceAllegro();

			virtual void write(const std::string &text, const AE::Math::Point2 &position, const AE::Graphics::Color &color);

		private:
			//FT_Bitmap mBitmap;
			ALLEGRO_FONT *mFontFace;
		};
	}
}

#endif