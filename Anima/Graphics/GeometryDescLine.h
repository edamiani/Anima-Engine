#ifndef __AE_GRAPHICS_GEOMETRY_DESC_LINE__
#define __AE_GRAPHICS_GEOMETRY_DESC_LINE__

#include "Anima/Graphics/GeometryDesc.h"

#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescLine : public AE::Graphics::GeometryDesc
		{
			GeometryDescLine() : GeometryDesc(AE::Graphics::GT_LINE) {}

			AE::Graphics::Color color;
			AE::Math::Point2<AE::int32> positionEnd;
			AE::Math::Point2<AE::int32> positionStart;
			AE::Real thickness;
		};
	}
}

#endif