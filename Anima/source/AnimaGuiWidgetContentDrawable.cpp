#include "../include/AnimaGuiWidgetContentDrawable.h"
#include "../include/AnimaGraphicsSurfaceFactory.h"

namespace AE
{
	namespace Gui
	{
		WidgetContentDrawable::WidgetContentDrawable()
			: mSurface(0)
		{
		}

		WidgetContentDrawable::WidgetContentDrawable(const AE::Math::Point2 &dimensions)
			: mDimensions(dimensions)
		{
			mSurface = AE::Graphics::SurfaceFactory::getInstance()->createSurface(dimensions, AE::Graphics::AT_PRIMARY_VIDEO);
		}

		WidgetContentDrawable::~WidgetContentDrawable()
		{
			AE::Graphics::SurfaceFactory::getInstance()->destroySurface(mSurface);
		}

		void WidgetContentDrawable::setDimensions(const AE::Math::Point2 &dimensions)
		{
			if(mSurface)
				AE::Graphics::SurfaceFactory::getInstance()->destroySurface(mSurface);

			mSurface = AE::Graphics::SurfaceFactory::getInstance()->createSurface(dimensions, AE::Graphics::AT_PRIMARY_VIDEO);
		}
	}
}