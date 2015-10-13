#ifndef __AE_CONSOLE_DESC__
#define __AE_CONSOLE_DESC__

#include "AnimaEnums.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSKeyListener.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class Surface;

		namespace Font
		{
			class Face;
		}
	}

	namespace OS
	{
		class Window;
	}

	struct ConsoleDesc
	{
		AE::Graphics::Color						backgroundColor;
		char									caretCharacter;
		AE::Graphics::ColorFormat				colorFormat;
		AE::ConsoleStyle						consoleStyle;
		AE::Math::Point2<AE::uint>				dimensionsInCharacters;
		AE::Math::Point2<AE::uint>				dimensionsInPixels;
		AE::Graphics::Color						foregroundColor;
		std::string								registeredFontName;
	};
}

#endif