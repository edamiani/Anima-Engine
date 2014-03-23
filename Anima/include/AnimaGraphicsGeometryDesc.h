#ifndef __AE_GRAPHICS_GEOMETRY_DESC__
#define __AE_GRAPHICS_GEOMETRY_DESC__

#include "AnimaGraphicsEnums.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		struct GeometryDesc
		{
			GeometryDesc(AE::Graphics::GeometryType _geometryType) : geometryType(_geometryType), drawingSurface(0) {}

			AE::Graphics::Surface *drawingSurface;

		protected:
			AE::Graphics::GeometryType geometryType;
		};
	}
}

#endif