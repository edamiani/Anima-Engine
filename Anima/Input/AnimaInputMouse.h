#ifndef __AE_INPUT_MOUSE__
#define __AE_INPUT_MOUSE__

#include "AnimaInputDevice.h"
#include "AnimaInputEnums.h"
#include "AnimaMathPoint2.h"

namespace AE
{
	namespace Input
	{
		class Mouse : public AE::Input::Device
		{
		public:
							Mouse() {  }
			virtual			~Mouse() {  }

			virtual int		getAbsoluteX() = 0;
			virtual int		getAbsoluteY() = 0;
			virtual AE::Math::Point2	getCoordinates() = 0;
			virtual int		getRelativeX() = 0;
			virtual int		getRelativeY() = 0;
			virtual bool	isButtonDown(AE::Input::MouseButtonType button) = 0;
		};
	}
}

#endif