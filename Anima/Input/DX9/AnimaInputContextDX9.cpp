#include "../include/AnimaInputContextDX9.h"
#include "../include/AnimaInputMouseDX9.h"
#include "../include/AnimaOSWindowWin32.h"

namespace AE
{
	namespace Input
	{
		ContextDX9::ContextDX9(AE::OS::WindowWin32 *window)
			: mWindow(window)
		{
			HRESULT result = DirectInput8Create(mWindow->_getHInstance(), DIRECTINPUT_VERSION, 
				IID_IDirectInput8, (void**)&mDInput8, NULL); 
			assert(!FAILED(result));

			mJoystick = 0;
			mKeyboard = 0;
			mMouse = 0;
		}

		ContextDX9::~ContextDX9()
		{
			//if(mJoystick) delete mJoystick;
			//if(mKeyboard) delete mKeyboard;
			if(mMouse) delete mMouse;

			mDInput8->Release();
		}

		AE::Input::Joystick* ContextDX9::_createJoystick(bool buffered)
		{
			return 0;
		}

		AE::Input::Keyboard* ContextDX9::_createKeyboard(bool buffered)
		{
			return 0;
		}

		AE::Input::Mouse* ContextDX9::_createMouse(bool buffered)
		{
			return (new AE::Input::MouseDX9(this));
		}
	}
}