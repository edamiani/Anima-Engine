#ifndef __AE_GRAPHICS_GEOMETRY_DESC_ELLIPSE__
#define __AE_GRAPHICS_GEOMETRY_DESC_ELLIPSE__

#include "AnimaGraphicsGeometryDesc.h"

#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescEllipse : public AE::Graphics::GeometryDesc
		{
			GeometryDescEllipse() : GeometryDesc(AE::Graphics::GT_ELLIPSE) {}

			AE::Graphics::Color borderColor;
			AE::Real borderThickness;
			AE::Math::Point2<AE::int32> center;
			AE::Graphics::Color fillColor;
			bool isFilled;
			AE::Math::Point2<AE::int32> radii;
		};
	}
}

#endif