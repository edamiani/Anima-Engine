#include "../include/AnimaGuiWidgetContentGeometry.h"

#include "../include/AnimaGraphicsGeometryFactory.h"

namespace AE
{
	namespace Gui
	{
		WidgetContentGeometry::WidgetContentGeometry(AE::Graphics::GeometryDesc *geometryDesc)
			: mGeometryDesc(geometryDesc)
		{
		}

		WidgetContentGeometry::~WidgetContentGeometry()
		{
		}
	}
}