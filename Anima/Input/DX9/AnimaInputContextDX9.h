#ifndef __AE_INPUT_CONTEXT_DX9__
#define __AE_INPUT_CONTEXT_DX9__

#define DIRECTINPUT_VERSION 0x0800

#include "AnimaInputContext.h"
#include "AnimaOSWindowWin.h"
#include "DInput.h"

namespace AE
{
	namespace OS
	{
		class WindowWin32;
	}

	namespace Input
	{
		class ContextDX9 : public AE::Input::Context
		{
		public:
			ContextDX9(AE::OS::WindowWin32 *window);
			~ContextDX9();

			LPDIRECTINPUT8  _getDInput8() { return mDInput8; }
			HWND _getWindowHandle() { return mWindow->_getWindowHandle(); }

		protected:
			Joystick*	_createJoystick(bool buffered = false);
			Keyboard*	_createKeyboard(bool buffered = false);
			Mouse*		_createMouse(bool buffered = false);

			LPDIRECTINPUT8  mDInput8;
			AE::OS::WindowWin32 *mWindow;
			HWND mWindowHandle;
		};
	}
}

#endif