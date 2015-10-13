#ifndef __AE_INPUT_CONTEXT__
#define __AE_INPUT_CONTEXT__

namespace AE
{
	namespace Input
	{
		class Joystick;
		class Keyboard;
		class Mouse;

		class Context
		{
		public:
			Context();
			virtual ~Context();

			AE::Input::Joystick*	acquireJoystick();
			AE::Input::Keyboard*	acquireKeyboard();
			AE::Input::Mouse*		acquireMouse();

		protected:
			virtual AE::Input::Joystick*	_createJoystick(bool buffered = false) = 0;
			virtual AE::Input::Keyboard*	_createKeyboard(bool buffered = false) = 0;
			virtual AE::Input::Mouse*		_createMouse(bool buffered = false) = 0;

			AE::Input::Joystick *mJoystick;
			AE::Input::Keyboard *mKeyboard;
			AE::Input::Mouse *mMouse;
		};
	}
}

#endif