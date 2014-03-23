#include "../include/AnimaGuiWidgetContentImage.h"

#include "../include/AnimaGraphicsImage.h"

namespace AE
{
	namespace Gui
	{
		WidgetContentImage::WidgetContentImage(AE::Graphics::Image *image)
			: mImage(image)
		{
			setDimensions(mImage->getDimensions());
		}

		WidgetContentImage::~WidgetContentImage()
		{
			mImage = 0;
		}
	}
}