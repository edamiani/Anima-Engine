#ifndef __AE_GRAPHICS_GEOMETRY_DESC_PIE__
#define __AE_GRAPHICS_GEOMETRY_DESC_PIE__

#include "AnimaGraphicsGeometryDesc.h"

#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescPie : public AE::Graphics::GeometryDesc
		{
			GeometryDescPie() : GeometryDesc(AE::Graphics::GT_PIE) {}

			AE::Graphics::Color borderColor;
			AE::Graphics::BorderPosition borderPosition;
			AE::Real borderThickness;
			AE::Math::Point2<AE::int32> center;
			AE::Graphics::Color fillColor;
			bool isFilled;
			AE::uint numSlices;
			AE::Math::Point2<AE::int32> radii;
			AE::uint totalSlices;
		};
	}
}

#endif