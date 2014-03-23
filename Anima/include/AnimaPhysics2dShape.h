/*
-----------------------------------------------------------------------------
Module: AE::Physics2d

Class: Shape

Description: 2d shape used to define collision area
-----------------------------------------------------------------------------
*/

#ifndef __AE_PHYSICS2D_SHAPE__
#define __AE_PHYSICS2D_SHAPE__

#include "AnimaPhysics2dShapeDesc.h"

namespace AE
{
	namespace Physics2d
	{
		class Shape
		{
		public:
			Shape(AE::Physics::ShapeType shapeType) : mShapeType(shapeType) { }
			virtual Shape() { }

			AE::Physics2d::ShapeType getType() { return mShapeType; }

		protected:
			AE::Physics2d::ShapeType mShapeType;
		};
	}
}