#include "../include/AnimaGraphicsFontFactoryFT.h"

#include "../include/AnimaGraphicsEnums.h"
#include "../include/AnimaGraphicsFontManagerFT.h"
#include "../include/AnimaGraphicsFontFaceFT.h"

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			AE::Graphics::Font::Face* FactoryFT::createFontFace(const AE::Graphics::Font::FaceDesc &fontFaceDesc)
			{
				AE::Graphics::Font::ManagerFT *fontManager = static_cast<AE::Graphics::Font::ManagerFT *>(AE::Graphics::Font::Manager::getInstance());
				FT_Face newFace;
				FT_Error error = FT_New_Face(fontManager->_getFreeTypeLibrary(), mRegisteredFonts[fontFaceDesc.registeredFontName].c_str(), 0, &newFace);
				assert(error != FT_Err_Unknown_File_Format);
				assert(error == 0);

				//error = FT_Set_Char_Size(newFace, fontFaceDesc.glyphDimensions.x * 64,  fontFaceDesc.glyphDimensions.y * 64, fontFaceDesc.horizontalResolution, fontFaceDesc.verticalResolution);
				//error = FT_Set_Pixel_Sizes(newFace, fontFaceDesc.glyphDimensions.x, fontFaceDesc.glyphDimensions.y);
				FT_Size_RequestRec sizeRequest;

				if(fontFaceDesc.fontOptions & AE::Graphics::FO_CELL_TYPE)
					sizeRequest.type       = FT_SIZE_REQUEST_TYPE_CELL;
				else
					sizeRequest.type       = FT_SIZE_REQUEST_TYPE_NOMINAL;

				sizeRequest.width          = fontFaceDesc.glyphDimensions.x << 6;
				sizeRequest.height         = fontFaceDesc.glyphDimensions.y << 6;
				sizeRequest.horiResolution = 0;
				sizeRequest.vertResolution = 0;
				
				error = FT_Request_Size(newFace, &sizeRequest);
				assert(error == 0);
				
				AE::Graphics::Font::Face *fontFace = new AE::Graphics::Font::FaceFT(newFace, fontFaceDesc);
				return fontFace;
			}

			void FactoryFT::destroyFontFace(AE::Graphics::Font::Face *fontFace)
			{
				// Is there a need to delete the FT_FACE instance?

				delete fontFace;
			}
		}
	}
}