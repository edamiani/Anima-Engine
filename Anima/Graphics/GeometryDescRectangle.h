#ifndef __AE_GRAPHICS_GEOMETRY_DESC_RECTANGLE__
#define __AE_GRAPHICS_GEOMETRY_DESC_RECTANGLE__

#include "Anima/Graphics/GeometryDesc.h"

#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"
#include "Anima/Math/Vector2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescRectangle : public AE::Graphics::GeometryDesc
		{
			GeometryDescRectangle() : GeometryDesc(AE::Graphics::GT_RECTANGLE), cornerRadii(0, 0) {}

			AE::Graphics::Color borderColor;
			AE::Real borderThickness;
			AE::Math::Point2<AE::Real> cornerRadii;
			AE::Math::Point2<AE::int32> positionBottomRight;
			AE::Math::Point2<AE::int32> positionTopLeft;
			AE::Graphics::Color fillColor;
			bool isFilled;
		};
	}
}

#endif