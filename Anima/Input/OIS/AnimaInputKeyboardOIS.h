#ifndef __AE_INPUT_KEYBOARD_OIS__
#define __AE_INPUT_KEYBOARD_OIS__

#include "AnimaInputKeyboard.h"
#include "OIS.h"

namespace AE
{
	namespace Input
	{
		class KeyboardOIS : public AE::Input::Keyboard
		{
		public:
							KeyboardOIS(OIS::Keyboard *keyboard) { mOISKeyboard = keyboard; }
							~KeyboardOIS() { mOISKeyboard = 0; }

			void			capture() { mOISKeyboard->capture(); }
			bool			isKeyDown(AE::Input::KeyCode code) { return mOISKeyboard->isKeyDown(static_cast<OIS::KeyCode>(code)); }

		private:
			OIS::Keyboard	*mOISKeyboard;
		};
	}
}

#endif