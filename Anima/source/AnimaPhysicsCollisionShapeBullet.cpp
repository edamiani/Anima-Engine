#include "../include/AnimaPhysicsCollisionShapeBullet.h"

namespace AE
{
	namespace Physics
	{
		CollisionShapeBullet::CollisionShapeBullet(const AE::Physics::CollisionShapeDesc &collisionShapeDesc)
		{
			mName = collisionShapeDesc.name;
			btVector3 size = btVector3(collisionShapeDesc.size.x / 2.0f, collisionShapeDesc.size.y / 2.0f, collisionShapeDesc.size.z / 2.0f);

			if(collisionShapeDesc.collisionShapeType == AE::Physics::CS_BOX)
				mCollisionShape = new btBoxShape(size);

			//mCollisionShape->calculateLocalInertia(static_cast<btScalar>(100.0f), btVector3(0.0f, 0.0f, 0.0f));
		}

		CollisionShapeBullet::~CollisionShapeBullet()
		{
			assert(mCollisionShape);
			delete mCollisionShape;
		}
	}
}