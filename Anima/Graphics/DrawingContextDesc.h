#ifndef __AE_GRAPHICS_DRAWING_CONTEXT_DESC__
#define __AE_GRAPHICS_DRAWING_CONTEXT_DESC__

#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"

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