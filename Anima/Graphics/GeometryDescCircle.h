#ifndef __AE_GRAPHICS_GEOMETRY_DESC_CIRCLE__
#define __AE_GRAPHICS_GEOMETRY_DESC_CIRCLE__

#include "Anima/Graphics/GeometryDesc.h"

#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescCircle : public AE::Graphics::GeometryDesc
		{
			GeometryDescCircle() : GeometryDesc(AE::Graphics::GT_CIRCLE) {}

			AE::Graphics::Color borderColor;
			AE::Real borderThickness;
			AE::Math::Point2<AE::int32> center;
			AE::Graphics::Color fillColor;
			bool isFilled;
			AE::Real radius;
		};
	}
}

#endif