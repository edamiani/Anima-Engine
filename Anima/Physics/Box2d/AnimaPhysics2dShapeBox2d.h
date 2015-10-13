/*
-----------------------------------------------------------------------------
Module: AE::Physics2d

Class: ShapeBox2d

Description: Realization of a 2d shape using Box2d
-----------------------------------------------------------------------------
*/

#ifndef __AE_PHYSICS2D_SHAPE_BOX2D__
#define __AE_PHYSICS2D_SHAPE_BOX2D__

#include "AnimaPhysics2dShape.h"

class b2Shape;

namespace AE
{
	namespace Physics2d
	{
		class ShapeBox2d
		{
		public:
			ShapeBox2d(const AE::Physics::ShapeDesc &shapeDesc);
			ShapeBox2d();

			/***** Inherited from AE::Physics2d::Shape
			AE::Physics2d::ShapeType getType();
			*****/

		protected:
			b2Shape *mShape;
			/***** Inherited from AE::Physics2d::Shape
			AE::Physics2d::ShapeType mShapeType;
			*****/
		};
	}
}