#ifndef __AE_GRAPHICS_GEOMETRY_DESC_DONUT__
#define __AE_GRAPHICS_GEOMETRY_DESC_DONUT__

#include "AnimaGraphicsGeometryDesc.h"

#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescDonut : public AE::Graphics::GeometryDesc
		{
			GeometryDescDonut() : GeometryDesc(AE::Graphics::GT_DONUT) {}

			AE::Graphics::Color borderColor;
			AE::Graphics::BorderPosition borderPosition;
			AE::Real borderThickness;
			AE::Math::Point2<AE::int32> center;
			AE::Real deltaAngle;
			AE::Graphics::Color fillColor;
			bool isFilled;
			AE::Math::Point2<AE::int32> radii;
			AE::Real startAngle;
		};
	}
}

#endif