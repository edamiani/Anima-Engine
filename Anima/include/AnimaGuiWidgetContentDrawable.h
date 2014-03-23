#ifndef __AE_GUI_WIDGET_CONTENT_DRAWABLE__
#define __AE_GUI_WIDGET_CONTENT_DRAWABLE__

#include "AnimaGuiWidgetContent.h"
#include "AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;
	}

	namespace Gui
	{
		class WidgetContentDrawable : public AE::Gui::WidgetContent
		{
		public:
			WidgetContentDrawable();
			WidgetContentDrawable(const AE::Math::Point2 &dimensions);
			virtual ~WidgetContentDrawable();

			AE::Math::Point2& getDimensions() { return mDimensions; }
			void setDimensions(const AE::Math::Point2 &dimensions);

			virtual void render() = 0;

		protected:
			AE::Math::Point2 mDimensions;
			AE::Graphics::Surface *mSurface;
		};
	}
}

#endif