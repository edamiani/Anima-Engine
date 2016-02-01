#ifndef __AE_GRAPHICS_GEOMETRY_FACTORY__
#define __AE_GRAPHICS_GEOMETRY_FACTORY__

#include "Anima/Graphics/Enums.h"
#include "Anima/Graphics/GeometryDescArc.h"
#include "Anima/Graphics/GeometryDescCircle.h"
#include "Anima/Graphics/GeometryDescDonut.h"
#include "Anima/Graphics/GeometryDescEllipse.h"
#include "Anima/Graphics/GeometryDescLine.h"
#include "Anima/Graphics/GeometryDescPie.h"
#include "Anima/Graphics/GeometryDescRectangle.h"
#include "Anima/Graphics/GeometryDescSpline.h"
#include "Anima/Graphics/GeometryDescTriangle.h"
#include "Anima/Math/Point2.h"

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