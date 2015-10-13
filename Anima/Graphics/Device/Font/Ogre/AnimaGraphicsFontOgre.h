#ifndef __AE_GRAPHICS_FONT_OGRE__
#define __AE_GRAPHICS_FONT_OGRE__

#include "AnimaGraphicsFont.h"
#include "Ogre.h"
#include "OgreFont.h"

namespace AE
{
	namespace Graphics
	{
		class FontOgre
		{
		public:
			FontOgre(const std::string &fontFace, AE::Real size, AE::Graphics::FontType fontType = AE::Graphics::FT_TRUETYPE) 
			{
				/*Ogre::String fontName(fontFace + Ogre::StringConverter::parseReal(size));
				mOgreFont = Ogre::FontManager::getSingleton().create(fontName, "AnimaEngine");
				
				if(fontType == AE::Graphics::FT_TRUETYPE)
				{
					mOgreFont->setType(Ogre::FT_TRUETYPE);
					mOgreFont->setTrueTypeSize(size);
				}
				else
					mOgreFont->setType(Ogre::FT_IMAGE);*/
			}

			virtual ~FontOgre() { /*mOgreFont.release();*/ }

		protected:
			Ogre::FontPtr	mOgreFont;
		};
	}
}

#endif