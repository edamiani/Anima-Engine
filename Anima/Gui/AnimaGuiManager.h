#ifndef __AE_GUI_MANAGER__
#define __AE_GUI_MANAGER__

#include "AnimaPrerequisites.h"
//#include "AnimaGraphicsFontUtilities.h"
#include "Ogre.h"
#include "OgrePanelOverlayElement.h"

namespace AE
{	
	namespace Gui
	{
		class Manager 
		{
		public:			
			Manager() 
			{
				mOverlay = Ogre::OverlayManager::getSingleton().create("AnimaGUIManager");
				mOverlay->show();
				
				Ogre::FontPtr ogreFont = Ogre::FontManager::getSingleton().create("Arial12", "AnimaEngine");
				ogreFont->setSource("Arial.ttf");
				ogreFont->setType(Ogre::FT_TRUETYPE);
				ogreFont->setTrueTypeSize(12);
				ogreFont->setTrueTypeResolution(72);
				ogreFont->addCodePointRange(Ogre::Font::CodePointRange(30, 128));
				ogreFont->load();
				//ogreFont->getMaterial()->setTextureFiltering(Ogre::TFO_NONE);
				ogreFont->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)->setTextureFiltering(Ogre::FO_NONE, Ogre::FO_NONE, Ogre::FO_NONE);
				
				//AE::Graphics::FontUtilities::generateFontTexture("Arial12");
				
				Ogre::OverlayContainer *overlayContainer = static_cast<Ogre::OverlayContainer*>(Ogre::OverlayManager::getSingleton().createOverlayElement("TextArea", "AEText"));
				static_cast<Ogre::PanelOverlayElement*>(overlayContainer)->setMetricsMode(Ogre::GMM_PIXELS);
				overlayContainer->setDimensions(256, 256);
				overlayContainer->setPosition(100, 100);
				Ogre::String fontName = ogreFont->getName();
				overlayContainer->setParameter("font_name", fontName);
				overlayContainer->setParameter("char_height", Ogre::StringConverter::toString(18));
				overlayContainer->setCaption("AIUEOmajejujomeinimujijejijiji");
				mOverlay->add2D(overlayContainer);
				overlayContainer->show();
			}
			~Manager() {}
			
		protected:
			Ogre::Overlay*			mOverlay;				// Main sheet overlay
		};
	} // End of Namespace Gui
} // End of Namespace AE

#endif