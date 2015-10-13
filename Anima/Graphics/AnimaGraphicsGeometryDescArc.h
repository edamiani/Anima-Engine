#ifndef __AE_GRAPHICS_GEOMETRY_DESC_ARC__
#define __AE_GRAPHICS_GEOMETRY_DESC_ARC__

#include "AnimaGraphicsGeometryDesc.h"

#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"

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