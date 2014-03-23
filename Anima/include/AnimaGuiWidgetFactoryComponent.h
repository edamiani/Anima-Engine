#ifndef __AE_GUI_WIDGET_FACTORY_COMPONENT__
#define __AE_GUI_WIDGET_FACTORY_COMPONENT__

#include "AnimaGuiWidgetDesc.h"

#include <string>

namespace AE
{
	namespace Gui
	{
		class Widget;

		class WidgetFactoryComponent
		{
		public:
			WidgetFactoryComponent() {}
			virtual ~WidgetFactoryComponent() {}

			virtual AE::Gui::Widget* create(const AE::Gui::WidgetDesc &widgetDesc) = 0;
			virtual void destroy(AE::Gui::Widget* widget) = 0;
		};
	}
}

#endif