#include "../include/AnimaGuiContainer.h"

namespace AE
{
	namespace Gui
	{
		Container::Container(AE::int32 id, const AE::Math::Point2 &position, const AE::Math::Point2 &dimensions)
			: Widget(id), mPosition(position), mDimensions(dimensions)
		{
		}

		Container::~Container()
		{
			mChildren.clear();
		}

		void Container::attachWidget(AE::Gui::Widget *widget, const AE::Math::Point2 &position)
		{
			mChildren.push_back(widget);
			mChildrenPosition[widget->getId()] = position;
		}

		void Container::render()
		{
		}
	}
}