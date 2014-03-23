#ifndef __AE_GRAPHICS_TRANSFORMATION_2D_DESC__
#define __AE_GRAPHICS_TRANSFORMATION_2D_DESC__

#include "AnimaMathPoint2.h"
#include "AnimaTypes.h"

namespace AE
{
	namespace Graphics
	{
		struct Transformation2dDesc
		{
			AE::Math::Point2<AE::int32>	position;
			AE::Real					rotation;
			AE::Math::Point2<AE::int32>	scale;
			AE::Real					zDepth;

			Transformation2dDesc()
				: position(AE::Math::Point2<AE::int32>(0, 0)), rotation(.0), scale(AE::Math::Point2<AE::int32>(0, 0)), zDepth(.0) {}
		};
	}
}

#endif