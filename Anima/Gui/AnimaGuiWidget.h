#ifndef __AE_GUI_WIDGET__
#define __AE_GUI_WIDGET__

#include "AnimaTypes.h"
#include "AnimaGuiEnums.h"

#include <list>

namespace AE
{
	namespace Gui
	{
		class WidgetContentDrawable;

		class Widget
		{
		public:
			Widget(AE::int32 id) : mId(id) {}
			virtual ~Widget() {}

			AE::int32 getId() { return mId; }
			virtual void render() = 0;

		protected:
			AE::int32 mId;
			AE::Gui::WidgetType mWidgetType;

			std::list<AE::Gui::WidgetContentDrawable *> mDrawables;
		};
	}
}

#endif