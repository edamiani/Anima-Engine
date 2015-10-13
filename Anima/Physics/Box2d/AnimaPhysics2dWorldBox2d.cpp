#include "../include/AnimaPhysicsWorld2d_Box2d.h"

#include "Box2D/Box2D.h"

namespace AE
{
	namespace Physics
	{
		World2d_Box2d::World2d_Box2d(const AE::Math::Vector2 &gravity)
		{
			mWorld = new b2World(b2Vec2(gravity.x, gravity.y));
		}

		World2d_Box2d::~World2d_Box2d()
		{
			delete mWorld;
		}
	}
}