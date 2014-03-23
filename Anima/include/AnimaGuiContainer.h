#ifndef __AE_GUI_CONTAINER__
#define __AE_GUI_CONTAINER__

#include "AnimaGuiWidget.h"
#include "AnimaMathPoint2.h"

#include <list>
#include <map>

namespace AE
{
	namespace Gui
	{
		class Container : public AE::Gui::Widget
		{
		public:
			Container(AE::int32 id, const AE::Math::Point2 &position, const AE::Math::Point2 &dimensions);
			virtual ~Container();

			void attachWidget(AE::Gui::Widget *widget, const AE::Math::Point2 &position);
			void render();

		protected:
			AE::Math::Point2 mDimensions;
			AE::Math::Point2 mPosition;

			std::list<AE::Gui::Widget *> mChildren;
			std::map<AE::int32, AE::Math::Point2> mChildrenPosition;
		};
	}
}

#endif