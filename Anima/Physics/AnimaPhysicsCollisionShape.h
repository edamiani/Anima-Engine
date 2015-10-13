#ifndef __AE_PHYSICS_COLLISION_SHAPE__
#define __AE_PHYSICS_COLLISION_SHAPE__

#include "AnimaPrerequisites.h"
#include "AnimaPhysicsManager.h"
#include "AnimaMathVector3.h"

namespace AE
{
	namespace Physics
	{
		struct CollisionShapeDesc
		{
			AE::Physics::CollisionShapeType	collisionShapeType;
			std::string						name;
			AE::Math::Vector3				size;

			CollisionShapeDesc()
			{
				collisionShapeType = AE::Physics::CS_BOX;
				name = "";
				size = AE::Math::Vector3::UNIT_SCALE;
			}

			~CollisionShapeDesc() { }
		};

		class CollisionShape
		{
		public:
			CollisionShape() { }
			virtual ~CollisionShape() { }

		protected:
			std::string mName;
		};
	}
}

#endif