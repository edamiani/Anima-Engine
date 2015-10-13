#ifndef __AE_GUI_WIDGET_CONTENT_IMAGE__
#define __AE_GUI_WIDGET_CONTENT_IMAGE__

#include "AnimaGuiWidgetContentDrawable.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		class Image;
	}

	namespace Gui
	{
		class WidgetContentImage : public AE::Gui::WidgetContentDrawable
		{
		public:
			WidgetContentImage(AE::Graphics::Image *image);
			virtual ~WidgetContentImage();

			void render() {}

		protected:
			AE::Graphics::Image *mImage;
		};
	}
}

#endif