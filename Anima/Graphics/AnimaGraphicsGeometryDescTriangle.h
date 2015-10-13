#ifndef __AE_GRAPHICS_GEOMETRY_DESC_TRIANGLE__
#define __AE_GRAPHICS_GEOMETRY_DESC_TRIANGLE__

#include "AnimaGraphicsGeometryDesc.h"

#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"
#include "../Math/AnimaMathVector2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescTriangle : public AE::Graphics::GeometryDesc
		{
			GeometryDescTriangle() : GeometryDesc(AE::Graphics::GT_SPLINE) {}

			AE::Graphics::Color borderColor;
			AE::Real borderThickness;
			AE::Graphics::Color fillColor;
			bool isFilled;
			AE::Math::Point2<AE::int32> points[3];
		};
	}
}

#endif