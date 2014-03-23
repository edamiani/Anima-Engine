#include "../include/AnimaConsoleShell.h"

#include "../include/AnimaGraphicsDevicePixelBuffer.h"
#include "../include/AnimaGraphicsFontFace.h"
#include "../include/AnimaGraphicsFontFaceDesc.h"
#include "../include/AnimaGraphicsFontFactory.h"
#include "../include/AnimaGraphicsFontManager.h"
#include "../include/AnimaMathRectangle.h"
#include "../include/AnimaOSEvent.h"
#include "../include/AnimaOSTimerFactory.h"
#include "../include/AnimaOSTimerManager.h"
#include "../include/AnimaOSWindowManager.h"

namespace AE
{
	ConsoleShell::ConsoleShell(const AE::ConsoleDesc &consoleDesc)
		: AE::Console(consoleDesc), mCaret(consoleDesc.caretCharacter), mDimensionsInCharacters(consoleDesc.dimensionsInCharacters), mShouldPrintCaret(true)
	{
		AE::Graphics::Font::FaceDesc fontFaceDesc;
		
		fontFaceDesc.fontOptions = AE::Graphics::FO_MONOCHROME | AE::Graphics::FO_CELL_TYPE;
		fontFaceDesc.fontType = AE::Graphics::FT_TRUETYPE;
		fontFaceDesc.glyphDimensions.x = mCharacterDimensions.x = consoleDesc.dimensionsInPixels.x / mDimensionsInCharacters.x;
		fontFaceDesc.glyphDimensions.y = mCharacterDimensions.y = consoleDesc.dimensionsInPixels.y / mDimensionsInCharacters.y;
		fontFaceDesc.horizontalResolution = 72;
		fontFaceDesc.verticalResolution = 72;

		mFontFace = AE::Graphics::Font::Manager::getInstance()->createFontFace(consoleDesc.registeredFontName, fontFaceDesc);

		mCurrentPosition = mCurrentCaretPosition = AE::Math::Point2<AE::int32>(0, 0);

		AE::OS::WindowManager::getInstance()->getEventQueue()->registerKeyListener(this);

		mTimer = AE::OS::TimerManager::getInstance()->getTimerFactory()->createTimerPeriodic(500, 500, this);
		mTimer->start();
	}

	ConsoleShell::~ConsoleShell() 
	{
		mTimer->stop();

		AE::OS::WindowManager::getInstance()->getEventQueue()->unregisterKeyListener(this);

		AE::Graphics::Font::Manager::getInstance()->getFontFactory()->destroyFontFace(mFontFace);
	}

	void ConsoleShell::printCharacter(wchar_t character, const AE::Math::Point2<AE::int32> &coordinates) 
	{		
		AE::Math::Point2<AE::int32> positionInPixels(mCurrentPosition.x * mCharacterDimensions.x, mCurrentPosition.y * mCharacterDimensions.y);

		mCurrentPosition.x++;
		if(mCurrentPosition.x == mDimensionsInCharacters.x)
		{
			mCurrentPosition.x = 0;
			mCurrentPosition.y++;
		}

		mFontFace->print(mPixelBuffer, std::wstring(1, character), positionInPixels, mForegroundColor);
	}

	void ConsoleShell::render(AE::Graphics::Device::PixelBuffer *destPixelBuffer)
	{
		destPixelBuffer->blitFrom(mPixelBuffer, AE::Math::Point2<AE::uint>(0, 0), AE::Math::Point2<AE::uint>(mDimensionsInPixels.x, mDimensionsInPixels.y), AE::Math::Point2<AE::int32>(0, 0));
	}

	void ConsoleShell::onInterval()
	{
		AE::Math::Point2<AE::int32> positionInPixels(mCurrentCaretPosition.x * mCharacterDimensions.x, mCurrentCaretPosition.y * mCharacterDimensions.y);

		if(mShouldPrintCaret)
		{
			mFontFace->print(mPixelBuffer, std::wstring(1, '_'), positionInPixels, mForegroundColor);

			mShouldPrintCaret = false;
		}
		else
		{
			mFontFace->print(mPixelBuffer, std::wstring(1, AE::Input::KV_FILL), positionInPixels, mBackgroundColor);

			mShouldPrintCaret = true;
		}
	}

	void ConsoleShell::onKeyDown(const AE::OS::EventKeyboard &event)
	{
		if(event.keyInfo.keyValue == AE::Input::KV_BACKSPACE)
		{
			if(mCurrentPosition.x != 0)
			{
				mCurrentPosition.x--;
			}
			else
			{
				if(mCurrentPosition.y > 0)
				{
					mCurrentPosition.x = mDimensionsInCharacters.x - 1;
					mCurrentPosition.y--;
				}
			}

			AE::Math::Point2<AE::int32> positionInPixels(mCurrentPosition.x * mCharacterDimensions.x, mCurrentPosition.y * mCharacterDimensions.y);
			
			mFontFace->print(mPixelBuffer, std::wstring(1, AE::Input::KV_FILL), positionInPixels, mBackgroundColor);

			repositionCaret();
			//mTimer->restart();
		}
		else if(event.keyInfo.keyValue == AE::Input::KV_SPACE)
		{
			mCurrentPosition.x++;
			if(mCurrentPosition.x == mDimensionsInCharacters.x)
			{
				mCurrentPosition.x = 0;
				mCurrentPosition.y++;
			}

			repositionCaret();
			//mTimer->restart();
		}
		else if(event.keyInfo.keyValue == AE::Input::KV_ENTER)
		{
			mCurrentPosition.x = 0;
			mCurrentPosition.y++;

			repositionCaret();
			//mTimer->restart();
		}
	}

	void ConsoleShell::onKeyTranslation(const AE::OS::EventKeyTranslation &keyEvent)
	{
		// Non-printable characters
		if(keyEvent.character < 0x21)
			return;

		mPixelBuffer->lock(AE::Graphics::LT_READWRITE);
		printCharacter(keyEvent.character);
		mPixelBuffer->unlock();

		repositionCaret();
	}

	void ConsoleShell::repositionCaret()
	{
		AE::Math::Point2<AE::int32> positionInPixels(mCurrentCaretPosition.x * mCharacterDimensions.x, mCurrentCaretPosition.y * mCharacterDimensions.y);
		mFontFace->print(mPixelBuffer, std::wstring(1, '_'), positionInPixels, mBackgroundColor);
		
		mCurrentCaretPosition = mCurrentPosition;

		positionInPixels.x = mCurrentCaretPosition.x * mCharacterDimensions.x;
		positionInPixels.y = mCurrentCaretPosition.y * mCharacterDimensions.y;
		mFontFace->print(mPixelBuffer, std::wstring(1, '_'), positionInPixels, mForegroundColor);

		mTimer->restart();
	}
}