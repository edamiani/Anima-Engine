#ifndef __AE_GRAPHICS_GEOMETRY_FACTORY_ALLEGRO__
#define __AE_GRAPHICS_GEOMETRY_FACTORY_ALLEGRO__

#include "AnimaGraphicsGeometryFactory.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

namespace AE
{
	namespace Graphics
	{
		struct Color;
		class Manager;
		class Surface;

		class GeometryFactoryAllegro : public AE::Graphics::GeometryFactory
		{
		public:
			GeometryFactoryAllegro();
			~GeometryFactoryAllegro();

			void drawArc(const AE::Graphics::GeometryDescArc &geometryDesc);
			void drawCircle(const AE::Graphics::GeometryDescCircle &geometryDesc);
			void drawDonut(const AE::Graphics::GeometryDescDonut &geometryDesc);
			void drawEllipse(const AE::Graphics::GeometryDescEllipse &geometryDesc);
			void drawLine(const AE::Graphics::GeometryDescLine &geometryDesc);
			void drawPie(const AE::Graphics::GeometryDescPie &geometryDesc);
			void drawRectangle(const AE::Graphics::GeometryDescRectangle &geometryDesc);
			void drawSpline(const AE::Graphics::GeometryDescSpline &geometryDesc);
			void drawTriangle(const AE::Graphics::GeometryDescTriangle &geometryDesc);
		
		protected:
		};
	}
}

#endif