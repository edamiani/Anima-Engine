#include "../include/AnimaPhysics2dShapeBox2d.h"

#include "Box2d/Box2d.h"

namespace AE
{
	namespace Physics2d
	{
		ShapeBox2d::ShapeBox2d(const AE::Physics::ShapeDesc &shapeDesc)
		{
			mShape = new b2Shape();
			mShape->
		}

		ShapeBox2d::~ShapeBox2d()
		{
			delete mShape;
		}
	}
}