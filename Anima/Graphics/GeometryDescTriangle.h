#ifndef __AE_GRAPHICS_GEOMETRY_DESC_TRIANGLE__
#define __AE_GRAPHICS_GEOMETRY_DESC_TRIANGLE__

#include "Anima/Graphics/GeometryDesc.h"

#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"
#include "Anima/Math/Vector2.h"

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