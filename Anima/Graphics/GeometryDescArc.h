#ifndef __AE_GRAPHICS_GEOMETRY_DESC_ARC__
#define __AE_GRAPHICS_GEOMETRY_DESC_ARC__

#include "Anima/Graphics/GeometryDesc.h"

#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescArc : public AE::Graphics::GeometryDesc
		{
			GeometryDescArc() : GeometryDesc(AE::Graphics::GT_ARC) {}

			AE::Math::Point2<AE::int32> center;
			AE::Graphics::Color color;
			AE::Real deltaAngle;
			AE::Real radius;
			AE::Real startAngle;
			AE::Real thickness;
		};
	}
}

#endif