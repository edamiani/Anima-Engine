#ifndef __AE_GRAPHICS_DRAWING_CONTEXT_DESC__
#define __AE_GRAPHICS_DRAWING_CONTEXT_DESC__

#include "AnimaGraphicsEnums.h"
#include "../Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		struct DrawingContextDesc
		{
			AE::Math::Point2 dimensions;
			AE::Graphics::SurfaceFormat surfaceFormat;
		};
	}
}

#endif