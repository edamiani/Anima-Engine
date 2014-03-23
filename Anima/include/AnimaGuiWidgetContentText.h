#ifndef __AE_GUI_WIDGET_CONTENT_TEXT__
#define __AE_GUI_WIDGET_CONTENT_TEXT__

#include "AnimaGuiWidgetContentDrawable.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class FontFace;
	}

	namespace Gui
	{
		class WidgetContentText : public AE::Gui::WidgetContentDrawable
		{
		public:
			WidgetContentText(AE::Graphics::FontFace *fontFace, const std::string &initialText = "button");
			virtual ~WidgetContentText();

			void render() {}
			void setText(const std::string &text);

		protected:
			AE::Graphics::FontFace *mFontFace;
			std::string mText;
		};
	}
}

#endif