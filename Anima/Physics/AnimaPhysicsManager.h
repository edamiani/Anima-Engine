#ifndef __AE_ANIMA_PHYSICS_MANAGER__
#define __AE_ANIMA_PHYSICS_MANAGER__

#include "AnimaPrerequisites.h"

namespace AE
{
	namespace Physics
	{
		enum CollisionShapeType
		{
			CS_BOX,
			CS_CAPSULE,
			CS_CONVEX,
			CS_CYLINDER,
			CS_MESH,
			CS_PLANE,
			CS_SPHERE
		};

		enum RigidBodyType
		{
			RB_CHARACTER,
			RB_DYNAMIC,
			RB_KINEMATIC,
			RB_STATIC,
			RB_TRIGGER
		};

		class Manager
		{
		public:
			Manager() { }
			virtual ~Manager() { }

			virtual CollisionShape* createCollisionShape(const AE::Physics::CollisionShapeDesc &collisionShapeDesc) = 0;
			virtual RigidBody* createRigidBody(const AE::Physics::RigidBodyDesc &rigidBodyDesc) = 0;
			virtual void destroyCollisionShape(const std::string &name) = 0;
			virtual void destroyRigidBody(const std::string &name) = 0;
			virtual void initialize(AE::Framework *framework) = 0;
			virtual void update(AE::Real timeElapsed) = 0;

		protected:
			AE::Framework *mFramework;

			std::map<std::string, AE::Physics::CollisionShape *>				mCollisionShapes;
			std::map<std::string, AE::Physics::CollisionShape *>::iterator	mCollisionShapesIterator;
			std::map<std::string, AE::Physics::RigidBody *>					mRigidBodies;
			std::map<std::string, AE::Physics::RigidBody *>::iterator			mRigidBodiesIterator;
		};
	}
}

#endif