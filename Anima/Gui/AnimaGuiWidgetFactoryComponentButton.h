#ifndef __AE_GUI_WIDGET_FACTORY_COMPONENT_BUTTON__
#define __AE_GUI_WIDGET_FACTORY_COMPONENT_BUTTON__

#include "AnimaGuiWidgetFactoryComponent.h"

#include <string>

namespace AE
{
	namespace Gui
	{
		class WidgetFactoryComponentButton : public AE::Gui::WidgetFactoryComponent
		{
		public:
			WidgetFactoryComponentButton() {}
			~WidgetFactoryComponentButton() {}

			AE::Gui::Widget* create(const AE::Gui::WidgetDesc &widgetDesc);
			void destroy(AE::Gui::Widget* widget) {  }
		};
	}
}

#endif