#ifndef __AE_INPUT_JOYSTICK__
#define __AE_INPUT_JOYSTICK__

#include "AnimaInputDevice.h"
#include "AnimaInputAxis.h"
#include <vector>

namespace AE
{
	namespace Input
	{
		//! POV / HAT Joystick component
		struct Pov
		{
			Pov() : direction(0) {}

			static const int Centered  = 0x00000000;
			static const int North     = 0x00000001;
			static const int South     = 0x00000010;
			static const int East      = 0x00000100;
			static const int West      = 0x00001000;
			static const int NorthEast = 0x00000101;
			static const int SouthEast = 0x00000110;
			static const int NorthWest = 0x00001001;
			static const int SouthWest = 0x00001010;

			int direction;
		};

		//! A sliding axis - only used in Win32 Right Now
		struct Slider
		{
			Slider() : abX(0), abY(0) {};
			//! true if pushed, false otherwise
			int abX, abY;
		};

		/**
			Represents the state of the joystick
			All members are valid for both buffered and non buffered mode
			Sticks with zero values are not present on the device
		*/
		struct JoyStickState
		{
			JoyStickState() : buttons(0) { clear(); }

			//! Represents all the single axes on the device
			std::vector<Axis> mAxes;

			//! Represents the value of a POV. Maximum of 4
			Pov mPOV[4];

			//! Represent the max sliders
			Slider mSliders[4];

			//! Represents All Buttons By Bit (max buttons = 32)
			int buttons;

			//! Button Bit Test - returns true if down
			inline int buttonDown( int button ) const
			{
				return ((buttons & ( 1L << button )) == 0) ? false : true;
			}

			//! internal method
			void clear()
			{
				buttons = 0;
				for( std::vector<Axis>::iterator i = mAxes.begin(), e = mAxes.end(); i != e; ++i )
				{
					(*i).absOnly = true;	//Currently, joysticks only report Abs
					(*i).clear();
				}
			}
		};

		class Joystick : public AE::Input::Device
		{
		public:
							Joystick() {  }
			virtual			~Joystick() {  }

			virtual int		getAxis(int axisNum) = 0;
			virtual int		getAxisX() = 0;
			virtual int		getAxisY() = 0;
			virtual int		getMaxAxisValue() = 0;
			virtual int		getMinAxisValue() = 0;
			virtual bool	isButtonDown(short buttton) = 0;
		};
	}
}

#endif