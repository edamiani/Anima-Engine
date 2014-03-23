#include "../include/AnimaGraphicsFontManagerFT.h"

#include "../include/AnimaGraphicsFontFactoryFT.h"

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			ManagerFT::ManagerFT() 
			{
				mInstance = this;
			}

			ManagerFT::~ManagerFT() {}

			bool ManagerFT::install(AE::uint options)
			{
				if(mParent != 0)
				{
					FT_Error error = FT_Init_FreeType(&mFreeTypeLibrary);
					
					if(error)
						return false;

					mFontFactory = new AE::Graphics::Font::FactoryFT();

					mIsInstalled = true;

					return true;
				}
				else
					return false;
			}

			bool ManagerFT::uninstall()
			{
				delete mFontFactory;

				return true;
			}
		}
	}
}