#ifndef __AE_INPUT_EVENTS__
#define __AE_INPUT_EVENTS__

#include "AnimaInputJoystick.h"
#include "AnimaInputKeyboard.h"
#include "AnimaInputMouse.h"

namespace AE
{
	namespace Input
	{
		struct JoystickEvent
		{
			int axisPosition;
			int button;
		};

		struct KeyEvent
		{
			//! KeyCode of event
			AE::Input::KeyCode key;
			//! Text character, depends on current TextTranslationMode
			unsigned int text;
		};

		struct MouseEvent
		{
			MouseEvent() : absX(0), absY(0), buttons(0), relX(0), relY(0) {}
			
			int absX, absY;
			AE::Input::MouseButton buttonId;
			int buttons;
			int relX, relY;

			//! Button down test
			inline bool isButtonDown(MouseButton button) const
			{
				return ((buttons & (1L << button)) == 0) ? false : true;
			}

			//! Clear all the values
			void clear()
			{
				absX = absY = relX = relY = buttons = 0;
			}
		};
	}
}

#endif