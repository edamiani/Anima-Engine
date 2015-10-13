#ifndef __ANIMA_GRAPHICS_FONT_UTILITIES__
#define __ANIMA_GRAPHICS_FONT_UTILITIES__

#include "AnimaPrerequisites.h"
#include "Ogre.h"
#include "OgreFont.h"

namespace AE
{
	namespace Graphics
	{
		namespace FontUtilities
		{
			int generateFontTexture(const std::string &fontName, bool load = false)
			{
				Ogre::UTFString cache_name = "_cache";

				Ogre::FontPtr font = Ogre::FontManager::getSingleton().getByName(fontName);
				if(font.isNull()) return 1;

				if(font->getType() != Ogre::FT_TRUETYPE)
					return 1;

				if(!font->isLoaded())
					font->load();

				Ogre::String texname = font->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->getTextureName();
				

				Ogre::TexturePtr fontTexture = Ogre::TextureManager::getSingleton().getByName(texname);
				Ogre::HardwarePixelBufferSharedPtr fontBuffer = fontTexture->getBuffer();

				if(fontBuffer.isNull())
					return 1;

				// create a remporary buffer that holds the font
				size_t nBuffSize = fontBuffer->getSizeInBytes();
				Ogre::uint8* buffer = (Ogre::uint8*)calloc(nBuffSize, sizeof(Ogre::uint8)); 
				Ogre::PixelBox fontPb(fontBuffer->getWidth(), fontBuffer->getHeight(),fontBuffer->getDepth(), fontBuffer->getFormat(), buffer);          
				fontBuffer->blitToMemory(fontPb);
				
				// create new render texture
				Ogre::String texNameManual = "FontTextureRTT_"+font->getName();
				Ogre::TexturePtr t = Ogre::TextureManager::getSingleton().createManual(texNameManual,"General",Ogre::TEX_TYPE_2D,fontBuffer->getWidth(),fontBuffer->getHeight(),fontBuffer->getDepth(),1,fontBuffer->getFormat(), Ogre::TU_RENDERTARGET);
				Ogre::TexturePtr fontTextureRTT = Ogre::TextureManager::getSingleton().getByName(texNameManual);
				fontTextureRTT->getBuffer()->blitFromMemory(fontPb);		
				
				// now render to file
				Ogre::RenderTexture* pRenderTexture = fontTextureRTT->getBuffer()->getRenderTarget();
				pRenderTexture->update();
				Ogre::String outImageName = font->getName() + cache_name + ".png";
				pRenderTexture->writeContentsToFile(outImageName);

				// free stuff
				free(buffer);
				Ogre::TextureManager::getSingleton().remove(texNameManual);


				// save texture font infos
				Ogre::UTFString out_text = font->getName()+cache_name+"\n{\n\ttype\timage\n\tsource\t"+outImageName+"\n";

				Ogre::Font::CodePointRangeList ranges = font->getCodePointRangeList();
				for(Ogre::Font::CodePointRangeList::iterator it = ranges.begin(); it != ranges.end(); it++)
				{
					// iterate over all known glyphs
					for(Ogre::uint32 i=it->first;i<it->second;i++)
					{
						Ogre::Font::GlyphInfo gi(0, Ogre::Font::UVRect(), 0);
						try
						{
							gi = font->getGlyphInfo(i);
						}
						catch(...)
						{
							// catch code point not found error
							continue;
						}
						
						// create character
			#ifdef FONT_UNICODE
						wchar_t tmp[20];
						swprintf(tmp, 20, L"%c", i);
			#else
						char tmp[20] = "";
						sprintf(tmp, "%c", i);
			#endif
						out_text.append("\tglyph " + Ogre::UTFString(tmp) + " " + \
									Ogre::StringConverter::toString(gi.uvRect.left)+" "+ \
									Ogre::StringConverter::toString(gi.uvRect.top)+" "+ \
									Ogre::StringConverter::toString(gi.uvRect.right)+" "+ \
									Ogre::StringConverter::toString(gi.uvRect.bottom)+"\n");

					}
				}
				out_text.append("}\n");

				Ogre::String defFileName = font->getName() + cache_name + ".fontdef";
				std::ofstream f;
				f.open(defFileName.c_str());
				f << out_text;
				f.close();
				Ogre::LogManager::getSingleton().logMessage("generated font cache for font "+fontName+" ("+outImageName+", "+defFileName+")");

				if(load)
				{
					// reload to find the .fontdef file
					Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
					// load now
					Ogre::FontPtr cached_font = Ogre::FontManager::getSingleton().getByName(fontName+cache_name);
					if(cached_font.isNull()) return 1;
					cached_font->load();
					return 0;
				}
				return 0;
			}

		};
	}
}

#endif