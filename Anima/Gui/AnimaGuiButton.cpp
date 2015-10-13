#include "../include/AnimaGuiButton.h"
#include "../include/AnimaGuiWidgetContentDrawable.h"

namespace AE
{
	namespace Gui
	{
		Button::Button(AE::int32 id, const AE::Gui::ButtonDesc &buttonDesc)
			: Widget(id)
		{
			mDrawables.push_back(buttonDesc.background);
			mDrawables.push_back(buttonDesc.label);
		}

		void Button::render()
		{
			std::list<AE::Gui::WidgetContentDrawable *>::iterator i = mDrawables.begin();

			for(i; i != mDrawables.end(); i++);
			{
				if(*i)
					(*i)->render();
			}
		}
	}
}