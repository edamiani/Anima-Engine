#include "../include/AnimaPhysicsManagerBullet.h"
#include "../include/AnimaPhysicsCollisionShapeBullet.h"
#include "../include/AnimaPhysicsRigidBodyBullet.h"

namespace AE
{
	namespace Physics
	{
		ManagerBullet::ManagerBullet()
		{
			mBroadphase = 0;
			mCollisionConfiguration = 0;
			mDispatcher = 0;
			mDynamicsWorld = 0;
			mPickConstraint = 0;
			mSolver = 0;
		}

		ManagerBullet::~ManagerBullet()
		{
			if(mDynamicsWorld) delete mDynamicsWorld;
			if(mSolver) delete mSolver;
			if(mBroadphase) delete mBroadphase;
			if(mDispatcher) delete mDispatcher;
			if(mCollisionConfiguration) delete mCollisionConfiguration;
		}

		CollisionShape* ManagerBullet::createCollisionShape(const AE::Physics::CollisionShapeDesc &collisionShapeDesc)
		{
			AE::Physics::CollisionShapeBullet *shape = new AE::Physics::CollisionShapeBullet(collisionShapeDesc);
			mCollisionShapes[collisionShapeDesc.name] = shape;
			
			return shape;
		}

		RigidBody* ManagerBullet::createRigidBody(const AE::Physics::RigidBodyDesc &rigidBodyDesc)
		{
			AE::Physics::RigidBodyBullet *rigidBody = new AE::Physics::RigidBodyBullet(rigidBodyDesc);
			mRigidBodies[rigidBodyDesc.sprite->getName()] = rigidBody;
			mDynamicsWorld->addRigidBody(rigidBody->_getRigidBody());

			return rigidBody;
		}

		void ManagerBullet::destroyCollisionShape(const std::string &name)
		{
			AE::Physics::CollisionShape *collisionShape = mCollisionShapes[name];
			mCollisionShapes.erase(name);
			delete collisionShape;
		}

		void ManagerBullet::destroyRigidBody(const std::string &name)
		{
			AE::Physics::RigidBody *rigidBody = mRigidBodies[name];
			mDynamicsWorld->removeCollisionObject(static_cast<AE::Physics::RigidBodyBullet *>(rigidBody)->_getRigidBody());
			mRigidBodies.erase(name);
			delete rigidBody;
		}

		void ManagerBullet::initialize(AE::Framework *framework)
		{
			mFramework = framework;

			// Collision configuration contains default setup for memory, collision setup
			mCollisionConfiguration = new btDefaultCollisionConfiguration();

			// Use the default collision dispatcher.
			mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);

			//btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
			mBroadphase = new btDbvtBroadphase();

			//the default constraint solver.
			mSolver = new btSequentialImpulseConstraintSolver();

			mDynamicsWorld = new btDiscreteDynamicsWorld(mDispatcher, mBroadphase, mSolver, mCollisionConfiguration);

			mDynamicsWorld->setGravity(btVector3(0, -10, 0));
		}

		void ManagerBullet::update(AE::Real timeElapsed)
		{
			mDynamicsWorld->stepSimulation((btScalar)timeElapsed, 10);
		}
	}
}