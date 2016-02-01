#ifndef __AE_GRAPHICS_GEOMETRY_DESC_SPLINE__
#define __AE_GRAPHICS_GEOMETRY_DESC_SPLINE__

#include "Anima/Graphics/GeometryDesc.h"

#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Enums.h"

namespace AE
{
	namespace Graphics
	{
		struct GeometryDescSpline : public AE::Graphics::GeometryDesc
		{
			GeometryDescSpline() : GeometryDesc(AE::Graphics::GT_SPLINE), drawAll(false) {}

			void setPoints(AE::Real _points[8])
			{
				points[0] = _points[0];
				points[1] = _points[1];
				points[2] = _points[2];
				points[3] = _points[3];
				points[4] = _points[4];
				points[5] = _points[5];
				points[6] = _points[6];
				points[7] = _points[7];
			}

			AE::Graphics::Color color;
			bool drawAll;
			AE::Real points[8];
			AE::Real thickness;
		};
	}
}

#endif