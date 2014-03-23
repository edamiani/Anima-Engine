#ifndef __AE_CONSOLE__
#define __AE_CONSOLE__

#include "AnimaConsoleDesc.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBuffer;
		}

		namespace Font
		{
			class Face;
		}
	}

	namespace OS
	{
		class Window;
	}

	class Console
	{
	public:
		Console(const AE::ConsoleDesc &consoleDesc);
		virtual ~Console();

		virtual void						printCharacter(wchar_t character, const AE::Math::Point2<AE::int32> &coordinates) = 0;
		virtual void						render(AE::Graphics::Device::PixelBuffer *destPixelBuffer) = 0;

	protected:
		AE::Graphics::Color					mBackgroundColor;
		void								*mCharacterMatrix;
		char								mCaret;
		AE::ConsoleStyle					mConsoleStyle;
		AE::Math::Point2<AE::uint>			mDimensionsInCharacters;
		AE::Math::Point2<AE::uint>			mDimensionsInPixels;
		AE::Graphics::Font::Face			*mFontFace;
		AE::Graphics::Color					mForegroundColor;
		AE::Graphics::Device::PixelBuffer	*mPixelBuffer;
	};
}

#endif