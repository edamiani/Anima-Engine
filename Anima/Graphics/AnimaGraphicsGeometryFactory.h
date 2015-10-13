#ifndef __AE_GRAPHICS_GEOMETRY_FACTORY__
#define __AE_GRAPHICS_GEOMETRY_FACTORY__

#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsGeometryDescArc.h"
#include "AnimaGraphicsGeometryDescCircle.h"
#include "AnimaGraphicsGeometryDescDonut.h"
#include "AnimaGraphicsGeometryDescEllipse.h"
#include "AnimaGraphicsGeometryDescLine.h"
#include "AnimaGraphicsGeometryDescPie.h"
#include "AnimaGraphicsGeometryDescRectangle.h"
#include "AnimaGraphicsGeometryDescSpline.h"
#include "AnimaGraphicsGeometryDescTriangle.h"
#include "../Math/AnimaMathPoint2.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		struct Color;
		class Surface;

		class GeometryFactory
		{
		public:
			~GeometryFactory() { }

			static AE::Graphics::GeometryFactory*	getInstance() { assert(mInstance); return mInstance; }
			static AE::Graphics::GeometryFactory*	initialize();
			static void shutdown();

			virtual void drawArc(const AE::Graphics::GeometryDescArc &geometryDesc) = 0;
			virtual void drawCircle(const AE::Graphics::GeometryDescCircle &geometryDesc) = 0;
			virtual void drawDonut(const AE::Graphics::GeometryDescDonut &geometryDesc) = 0;
			virtual void drawEllipse(const AE::Graphics::GeometryDescEllipse &geometryDesc) = 0;
			virtual void drawLine(const AE::Graphics::GeometryDescLine &geometryDesc) = 0;
			virtual void drawPie(const AE::Graphics::GeometryDescPie &geometryDesc) = 0;
			virtual void drawRectangle(const AE::Graphics::GeometryDescRectangle &geometryDesc) = 0;
			virtual void drawSpline(const AE::Graphics::GeometryDescSpline &geometryDesc) = 0;
			virtual void drawTriangle(const AE::Graphics::GeometryDescTriangle &geometryDesc) = 0;
		
		protected:
			GeometryFactory();

			static AE::Graphics::GeometryFactory *mInstance;
		};
	}
}

#endif