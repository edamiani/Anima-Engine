#ifndef __AE_GUI_WIDGET_CONTENT_GEOMETRY__
#define __AE_GUI_WIDGET_CONTENT_GEOMETRY__

#include "AnimaGuiWidgetContentDrawable.h"

#include "AnimaGraphicsEnums.h"
#include "AnimaParameter.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		struct GeometryDesc;
	}

	namespace Gui
	{
		class WidgetContentGeometry : public AE::Gui::WidgetContentDrawable
		{
		public:
			WidgetContentGeometry(AE::Graphics::GeometryDesc *geometryDesc);
			virtual ~WidgetContentGeometry();

			void render() {}

		protected:
			AE::Graphics::GeometryDesc *mGeometryDesc;
		};
	}
}

#endif