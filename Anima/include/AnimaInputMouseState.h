#ifndef __AE_INPUT_MOUSE_STATE__
#define __AE_INPUT_MOUSE_STATE__

#include "AnimaMathVector2.h"

namespace AE
{
	namespace Input
	{
		struct MouseState
		{
		public:
			MouseState(const AE::Math::Vector2 &newCoordinates, bool buttons[3]) {  }
			virtual			~MouseState() {  }

			AE::Math::Vector2 coordinates;
			bool buttonsPressed[3];
		};
	}
}

#endif