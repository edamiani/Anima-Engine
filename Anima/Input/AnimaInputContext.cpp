#include "../include/AnimaInputContext.h"
#include "../include/AnimaPlatform.h"

namespace AE
{
	namespace Input
	{
		Context::Context()
		{
		}

		Context::~Context()
		{
		}

		Joystick* Context::acquireJoystick()
		{
			mJoystick = _createJoystick();
			return mJoystick;
		}

		Keyboard* Context::acquireKeyboard() 
		{
			mKeyboard = _createKeyboard();
			return mKeyboard; 
		};
		
		Mouse* Context::acquireMouse() 
		{
			mMouse = _createMouse();
			return mMouse; 
		};
	}
}