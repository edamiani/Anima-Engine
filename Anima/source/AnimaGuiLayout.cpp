#include "../include/AnimaGuiLayout.h"
#include "../include/AnimaGuiContainer.h"
#include "../include/AnimaGuiWidgetFactory.h"

namespace AE
{
	namespace Gui
	{
		Layout::Layout(const AE::Math::Point2 &position, const AE::Math::Point2 &dimensions)
		{
			mRoot = new AE::Gui::Container(AE::Gui::WidgetFactory::getInstance()->getNewId(), position, dimensions);
		}

		void Layout::render()
		{ 
			mRoot->render(); 
		}
	}
}