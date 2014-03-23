#include "../include/AnimaGuiWidgetContentText.h"

#include "../include/AnimaGraphicsFontFace.h"

namespace AE
{
	namespace Gui
	{
		WidgetContentText::WidgetContentText(AE::Graphics::FontFace *fontFace, const std::string &initialText)
			: mFontFace(fontFace), mText(initialText)
		{
			setDimensions(AE::Math::Point2(0, 0));
		}

		WidgetContentText::~WidgetContentText()
		{
			mFontFace = 0;
		}

		void WidgetContentText::setText(const std::string &text)
		{
			mText = text;
		}
	}
}