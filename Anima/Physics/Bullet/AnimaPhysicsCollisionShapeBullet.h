#ifndef __AE_PHYSICS_COLLISION_SHAPE_BULLET__
#define __AE_PHYSICS_COLLISION_SHAPE_BULLET__

#include "AnimaPhysicsCollisionShape.h"
#include "AnimaPhysicsManagerBullet.h"

namespace AE
{
	namespace Physics
	{
		class CollisionShapeBullet : public AE::Physics::CollisionShape
		{
		public:
			CollisionShapeBullet(const AE::Physics::CollisionShapeDesc &collisionShapeDesc);
			~CollisionShapeBullet();

			btCollisionShape* _getCollisionShape() { return mCollisionShape; }

		private:
			btCollisionShape* mCollisionShape;
		};
	}
}

#endif