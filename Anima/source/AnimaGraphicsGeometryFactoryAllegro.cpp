#include "../include/AnimaGraphicsColor.h"
#include "../include/AnimaGraphicsGeometryFactoryAllegro.h"
#include "../include/AnimaGraphicsSurfaceAllegro.h"
#include "../include/AnimaMathTrigonometry.h"

#include <cassert>
#include <cmath>

namespace AE
{
	namespace Graphics
	{
		GeometryFactoryAllegro::GeometryFactoryAllegro()
		{
			al_init_primitives_addon();
		}

		GeometryFactoryAllegro::~GeometryFactoryAllegro()
		{
			al_shutdown_primitives_addon();
		}

		void GeometryFactoryAllegro::drawArc(const AE::Graphics::GeometryDescArc &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);

			al_draw_arc(geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radius, geometryDesc.startAngle, geometryDesc.deltaAngle, al_map_rgba(geometryDesc.color.R, geometryDesc.color.G, geometryDesc.color.B, geometryDesc.color.A), geometryDesc.thickness);
		}

		void GeometryFactoryAllegro::drawCircle(const AE::Graphics::GeometryDescCircle &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);

			if(geometryDesc.isFilled)
				al_draw_filled_circle(geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radius, al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A));
			else
				al_draw_circle(geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radius, al_map_rgba(geometryDesc.borderColor.R, geometryDesc.borderColor.G, geometryDesc.borderColor.B, geometryDesc.borderColor.A), geometryDesc.borderThickness);
		}

		void GeometryFactoryAllegro::drawDonut(const AE::Graphics::GeometryDescDonut &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);

			ALLEGRO_VERTEX vertexCache[ALLEGRO_VERTEX_CACHE_SIZE];
			ALLEGRO_VERTEX vertexCache1[ALLEGRO_VERTEX_CACHE_SIZE];
			ALLEGRO_VERTEX vertexCache2[ALLEGRO_VERTEX_CACHE_SIZE];

			const ALLEGRO_TRANSFORM* t = al_get_current_transform();
			float scale = (hypot((t->m[0][0]), (t->m[0][1])) + hypot((t->m[1][0]), (t->m[1][1]))) / 2;

			assert(geometryDesc.radii.x >= 0);

			int numSegments = fabs(geometryDesc.deltaAngle / (2 * ALLEGRO_PI) * ALLEGRO_PRIM_QUALITY * scale * sqrtf(geometryDesc.radii.y));

			if (numSegments < 2)
				return;

			if (2 * numSegments >= ALLEGRO_VERTEX_CACHE_SIZE) 
			{
				numSegments = (ALLEGRO_VERTEX_CACHE_SIZE - 1) / 2;
			}

			al_calculate_arc(&(vertexCache1[0].x), sizeof(ALLEGRO_VERTEX), geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radii.x, geometryDesc.radii.x, geometryDesc.startAngle, geometryDesc.deltaAngle, 0, numSegments);
			al_calculate_arc(&(vertexCache2[0].x), sizeof(ALLEGRO_VERTEX), geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radii.y, geometryDesc.radii.y, geometryDesc.startAngle, geometryDesc.deltaAngle, 0, numSegments);

			if(geometryDesc.isFilled)
			{
				if(geometryDesc.radii.x > 0)
				{
					for (int i = 0; i < 2 * numSegments; i += 2)
					{
						int iByTwo = i / 2;
						vertexCache[i].x = vertexCache1[iByTwo].x;
						vertexCache[i].y = vertexCache1[iByTwo].y;
						vertexCache[i].z = 0;

						vertexCache[i + 1].x = vertexCache2[iByTwo].x;
						vertexCache[i + 1].y = vertexCache2[iByTwo].y;
						vertexCache[i + 1].z = 0;

						vertexCache[i].color = vertexCache[i + 1].color = al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A);
					}

					al_draw_prim(vertexCache, 0, 0, 0, 2 * numSegments, ALLEGRO_PRIM_TRIANGLE_STRIP);
				}
				else
				{
					vertexCache[0].x = geometryDesc.center.x;
					vertexCache[0].y = geometryDesc.center.y;
					vertexCache[0].z = 0;
					vertexCache[0].color = al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A);

					for (int i = 0; i < numSegments; i++)
					{
						vertexCache[i + 1].x = vertexCache2[i].x;
						vertexCache[i + 1].y = vertexCache2[i].y;
						vertexCache[i + 1].z = 0;
						vertexCache[i + 1].color = al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A);
					}

					al_draw_prim(vertexCache, 0, 0, 0, numSegments + 1, ALLEGRO_PRIM_TRIANGLE_FAN);
				}
			}

			if(geometryDesc.borderThickness > 0)
			{
				ALLEGRO_COLOR allegroBorderColor = al_map_rgba(geometryDesc.borderColor.R, geometryDesc.borderColor.G, geometryDesc.borderColor.B, geometryDesc.borderColor.A);
				
				if(geometryDesc.radii.x > 0)
					al_draw_arc(geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radii.x, geometryDesc.startAngle, geometryDesc.deltaAngle, allegroBorderColor, geometryDesc.borderThickness);

				al_draw_arc(geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radii.y, geometryDesc.startAngle, geometryDesc.deltaAngle, allegroBorderColor, geometryDesc.borderThickness);

				int lastSegment = numSegments - 1;
				int bleeding = geometryDesc.borderThickness / 2;
				al_draw_line(vertexCache1[0].x, vertexCache1[0].y, vertexCache2[0].x, vertexCache2[0].y, allegroBorderColor, geometryDesc.borderThickness);
				al_draw_line(vertexCache1[lastSegment].x, vertexCache1[lastSegment].y, vertexCache2[lastSegment].x, vertexCache2[lastSegment].y, allegroBorderColor, geometryDesc.borderThickness);
			}
		}

		void GeometryFactoryAllegro::drawEllipse(const AE::Graphics::GeometryDescEllipse &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);

			if(geometryDesc.isFilled)
				al_draw_filled_ellipse(geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radii.x, geometryDesc.radii.y, al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A));
			else
				al_draw_ellipse(geometryDesc.center.x, geometryDesc.center.y, geometryDesc.radii.x, geometryDesc.radii.y, al_map_rgba(geometryDesc.borderColor.R, geometryDesc.borderColor.G, geometryDesc.borderColor.B, geometryDesc.borderColor.A), geometryDesc.borderThickness);
		}

		void GeometryFactoryAllegro::drawLine(const AE::Graphics::GeometryDescLine &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			//drawingSurface->lock(lockType);
			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);
			al_draw_line(geometryDesc.positionStart.x, geometryDesc.positionStart.y, geometryDesc.positionEnd.x, geometryDesc.positionEnd.y, al_map_rgba(geometryDesc.color.R, geometryDesc.color.G, geometryDesc.color.B, geometryDesc.color.A), geometryDesc.thickness);

			//drawingSurface->unlock();
		}

		void GeometryFactoryAllegro::drawPie(const AE::Graphics::GeometryDescPie &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			AE::Real sliceArc = AE::Math::TWO_PI / geometryDesc.totalSlices;
			AE::Graphics::GeometryDescDonut donutDesc;
			donutDesc.drawingSurface = geometryDesc.drawingSurface;
			for(AE::uint i = 0; i < geometryDesc.numSlices; i++)
			{
				donutDesc.center = geometryDesc.center;
				donutDesc.radii = geometryDesc.radii;
				donutDesc.startAngle = AE::Math::PI_BY_2 + (i * sliceArc);
				donutDesc.deltaAngle = sliceArc;
				donutDesc.isFilled = geometryDesc.isFilled;
				donutDesc.fillColor = geometryDesc.fillColor;
				donutDesc.borderThickness = geometryDesc.borderThickness;
				donutDesc.borderColor = geometryDesc.borderColor;
				donutDesc.borderPosition = geometryDesc.borderPosition;
				drawDonut(donutDesc);
			}
		}

		void GeometryFactoryAllegro::drawRectangle(const AE::Graphics::GeometryDescRectangle &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);

			if(geometryDesc.cornerRadii.x < 0.01 || geometryDesc.cornerRadii.y < 0.01)
			{
				if(geometryDesc.isFilled)
					al_draw_filled_rectangle(geometryDesc.positionTopLeft.x, geometryDesc.positionTopLeft.y, geometryDesc.positionBottomRight.x, geometryDesc.positionBottomRight.y, al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A));
				else
					al_draw_rectangle(geometryDesc.positionTopLeft.x, geometryDesc.positionTopLeft.y, geometryDesc.positionBottomRight.x, geometryDesc.positionBottomRight.y, al_map_rgba(geometryDesc.borderColor.R, geometryDesc.borderColor.G, geometryDesc.borderColor.B, geometryDesc.borderColor.A), geometryDesc.borderThickness);
			}
			else
			{
				if(geometryDesc.isFilled)
					al_draw_filled_rounded_rectangle(geometryDesc.positionTopLeft.x, geometryDesc.positionTopLeft.y, geometryDesc.positionBottomRight.x, geometryDesc.positionBottomRight.y, geometryDesc.cornerRadii.x, geometryDesc.cornerRadii.y, al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A));
				else
					al_draw_rounded_rectangle(geometryDesc.positionTopLeft.x, geometryDesc.positionTopLeft.y, geometryDesc.positionBottomRight.x, geometryDesc.positionBottomRight.y, geometryDesc.cornerRadii.x, geometryDesc.cornerRadii.y, al_map_rgba(geometryDesc.borderColor.R, geometryDesc.borderColor.G, geometryDesc.borderColor.B, geometryDesc.borderColor.A), geometryDesc.borderThickness);
			}
		}

		void GeometryFactoryAllegro::drawSpline(const AE::Graphics::GeometryDescSpline &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);
			al_draw_spline(const_cast<float *>(geometryDesc.points), al_map_rgba(geometryDesc.color.R, geometryDesc.color.G, geometryDesc.color.B, geometryDesc.color.A), geometryDesc.thickness);
		}

		void GeometryFactoryAllegro::drawTriangle(const AE::Graphics::GeometryDescTriangle &geometryDesc)
		{
			assert(geometryDesc.drawingSurface);

			ALLEGRO_BITMAP *allegroBitmap = static_cast<AE::Graphics::SurfaceAllegro *>(geometryDesc.drawingSurface)->_getAllegroBitmap();
			al_set_target_bitmap(allegroBitmap);

			if(geometryDesc.isFilled)
				al_draw_filled_triangle(geometryDesc.points[0].x, geometryDesc.points[0].y, geometryDesc.points[1].x, geometryDesc.points[1].y, geometryDesc.points[2].x, geometryDesc.points[2].y, al_map_rgba(geometryDesc.fillColor.R, geometryDesc.fillColor.G, geometryDesc.fillColor.B, geometryDesc.fillColor.A));
			else
				al_draw_triangle(geometryDesc.points[0].x, geometryDesc.points[0].y, geometryDesc.points[1].x, geometryDesc.points[1].y, geometryDesc.points[2].x, geometryDesc.points[2].y, al_map_rgba(geometryDesc.borderColor.R, geometryDesc.borderColor.G, geometryDesc.borderColor.B, geometryDesc.borderColor.A), geometryDesc.borderThickness);
		}
	}
}