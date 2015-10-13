#ifndef __AE_GUI_BUTTON__
#define __AE_GUI_BUTTON__

#include "AnimaGuiWidget.h"
#include "AnimaGuiButtonDesc.h"

namespace AE
{
	namespace Gui
	{
		class Button : public AE::Gui::Widget
		{
		public:
			Button(AE::int32 id, const AE::Gui::ButtonDesc &buttonDesc);
			virtual ~Button() {}

			void render();

		protected:
		};
	}
}

#endif