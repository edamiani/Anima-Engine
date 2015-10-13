#ifndef __AE_GRAPHICS_FONT_MANAGER_FT__
#define __AE_GRAPHICS_FONT_MANAGER_FT__

#include "AnimaGraphicsFontManager.h"

#include "ft2build.h"
#include FT_FREETYPE_H 

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			class ManagerFT : public AE::Graphics::Font::Manager
			{
			public:
				ManagerFT();
				~ManagerFT();

				bool install(AE::uint options);
				bool uninstall();

				FT_Library _getFreeTypeLibrary() { return mFreeTypeLibrary; }

			private:
				FT_Library mFreeTypeLibrary;
			};	
		}
	}
}

#endif