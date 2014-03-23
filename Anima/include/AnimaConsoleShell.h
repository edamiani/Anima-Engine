#ifndef __AE_CONSOLE_SHELL__
#define __AE_CONSOLE_SHELL__

#include "AnimaConsole.h"
#include "AnimaOSKeyListener.h"
#include "AnimaOSTimerListener.h"
#include "AnimaOSTimerPeriodic.h"

namespace AE
{
	class ConsoleShell : public AE::Console, public AE::OS::TimerListener, public AE::OS::KeyListener
	{
	public:
		ConsoleShell(const AE::ConsoleDesc &consoleDesc);
		~ConsoleShell();

		void printCharacter(wchar_t character, const AE::Math::Point2<AE::int32> &coordinates = AE::Math::Point2<AE::int32>(0, 0));
		void render(AE::Graphics::Device::PixelBuffer *destPixelBuffer);

		void onInterval();

		void onKeyDown(const AE::OS::EventKeyboard &event);
		void onKeyTranslation(const AE::OS::EventKeyTranslation &event);

	protected:
		void repositionCaret();

		char						mCaret;
		AE::Math::Point2<AE::uint>	mCharacterDimensions;
		AE::Math::Point2<AE::int32>	mCurrentPosition;
		AE::Math::Point2<AE::int32>	mCurrentCaretPosition;
		AE::Math::Point2<AE::uint>	mDimensionsInCharacters;
		bool						mShouldPrintCaret;
		AE::OS::TimerPeriodic		*mTimer;
	};
}

#endif