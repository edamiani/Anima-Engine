#ifndef __AE_ANIMA_INPUT_MOUSE_OIS__
#define __AE_ANIMA_INPUT_MOUSE_OIS__

#include "AnimaInputMouse.h"
#include "AnimaInputContextDX9.h"

#include <cassert>

namespace AE
{
	namespace Input
	{
		class MouseDX9 : public AE::Input::Mouse
		{
		public:
			MouseDX9(AE::Input::ContextDX9 *inputContext);
			~MouseDX9();
	
			AE::int32	getAbsoluteX();
			AE::int32	getAbsoluteY();
			AE::Math::Point2	getCoordinates();
			AE::int32	getRelativeX();
			AE::int32	getRelativeY();
			bool		isButtonDown(AE::Input::MouseButtonType button);
			bool		poll();

		private:
			AE::Input::ContextDX9 *mInputContext;
			LPDIRECTINPUTDEVICE8 mMouseDI8;
			DIMOUSESTATE mMouseState;
			bool mIsAcquired;
		};
	}
}

#endif