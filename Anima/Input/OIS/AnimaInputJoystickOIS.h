#ifndef __AE_INPUT_JOYSTICK_OIS__
#define __AE_INPUT_JOYSTICK_OIS__

#include "AnimaInputJoystick.h"
#include "OIS.h"

namespace AE
{
	namespace Input
	{
		class JoystickOIS : public AE::Input::Joystick
		{
		public:
						JoystickOIS(OIS::JoyStick *joystick) { mOISJoystick = joystick; }
						~JoystickOIS() { mOISJoystick = 0; }

			void		capture() { mOISJoystick->capture(); }
			int			getAxis(int axisNum) { return mOISJoystick->getJoyStickState().mAxes[axisNum].abs; }
			//int		getAxisX() { return mOISJoystick->getJoyStickState().mAxes[mOISJoystick->axes() - 1].abs; }
			int			getAxisX() { return mOISJoystick->getJoyStickState().mAxes[mOISJoystick->getNumberOfComponents(OIS::OIS_Axis) - 1].abs; }
			//int		getAxisY() { return mOISJoystick->getJoyStickState().mAxes[mOISJoystick->axes() - 2].abs; }
			int			getAxisY() { return mOISJoystick->getJoyStickState().mAxes[mOISJoystick->getNumberOfComponents(OIS::OIS_Axis) - 2].abs; }
			int			getMaxAxisValue() { return mOISJoystick->MAX_AXIS; }
			int			getMinAxisValue() { return mOISJoystick->MIN_AXIS; }
			//bool		isButtonDown(short button) { if(mOISJoystick->buttons() >= button) return mOISJoystick->getJoyStickState().buttonDown(button); else return false; }
			bool		isButtonDown(short button) { return false; /*if(mOISJoystick->getNumberOfComponents(OIS::OIS_Button) >= button) return mOISJoystick->getJoyStickState().buttonDown(button); else return false;*/ }

		private:
			OIS::JoyStick		*mOISJoystick;
		};
	}
}

#endif