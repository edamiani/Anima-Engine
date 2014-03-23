#ifndef __AE_ANIMA_PHYSICS_MANAGER_BULLET__
#define __AE_ANIMA_PHYSICS_MANAGER_BULLET__

#include "AnimaPhysicsManager.h"
#include "AnimaGraphicsSprite.h"

#include "btBulletDynamicsCommon.h"
#include "btVector3.h"

namespace AE
{
	class Framework;

	namespace Physics
	{
		class ManagerBullet : public AE::Physics::Manager
		{
		public:
			ManagerBullet();
			~ManagerBullet();

			CollisionShape* createCollisionShape(const AE::Physics::CollisionShapeDesc &collisionShapeDesc);
			RigidBody* createRigidBody(const AE::Physics::RigidBodyDesc &rigidBodyDesc);
			void destroyCollisionShape(const std::string &name);
			void destroyRigidBody(const std::string &name);
			void initialize(AE::Framework *framework);
			void update(AE::Real timeElapsed);

			btDynamicsWorld* _getDynamicsWorld() { return mDynamicsWorld; }

		protected:
			//Bullet objects
			btBroadphaseInterface*	mBroadphase;
			btDefaultCollisionConfiguration* mCollisionConfiguration;
			btCollisionDispatcher*	mDispatcher;
			btDynamicsWorld*		mDynamicsWorld; // this is the most important class
			btTypedConstraint*		mPickConstraint; // constraint for mouse picking
			btSequentialImpulseConstraintSolver*		mSolver;
		};
	}
}

#endif