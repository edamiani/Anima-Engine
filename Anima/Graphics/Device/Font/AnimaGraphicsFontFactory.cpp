#include "../include/AnimaGraphicsFontFactory.h"

namespace AE
{
	namespace Graphics
	{
		namespace Font
		{
			Factory::Factory()
			{
			}

			Factory::~Factory()
			{
			}

			void Factory::registerFontFile(const std::string &fileName, const std::string &registeredName)
			{
				mRegisteredFonts[registeredName] = fileName;
			}

			void Factory::unregisterFontFile(const std::string &registeredName)
			{
				mRegisteredFonts.erase(registeredName);
			}
		}
	}
}