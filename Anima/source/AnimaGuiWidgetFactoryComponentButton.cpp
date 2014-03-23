#include "../include/AnimaGuiWidgetFactoryComponentButton.h"
#include "../include/AnimaGuiWidgetFactory.h"

#include "../include/AnimaGuiButton.h"

namespace AE
{
	namespace Gui
	{
		AE::Gui::Widget* WidgetFactoryComponentButton::create(const AE::Gui::WidgetDesc &widgetDesc)
		{
			AE::Gui::Button *button = new AE::Gui::Button(AE::Gui::WidgetFactory::getInstance()->getNewId(), static_cast<const AE::Gui::ButtonDesc &>(widgetDesc));

			return button;
		}
	}
}