#ifndef __AE_GUI_BUTTON_DESC__
#define __AE_GUI_BUTTON_DESC__

#include "AnimaGuiWidgetDesc.h"

#include "AnimaGuiWidgetContentImage.h"
#include "AnimaGuiWidgetContentText.h"

namespace AE
{
	namespace Gui
	{
		struct ButtonDesc : public AE::Gui::WidgetDesc
		{
		public:
			ButtonDesc() : background(0), label(0) {}
			~ButtonDesc() {}

			AE::Gui::WidgetContentImage *background;
			AE::Gui::WidgetContentText *label;
		};
	}
}

#endif