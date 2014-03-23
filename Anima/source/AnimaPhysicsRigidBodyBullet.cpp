#include "../include/AnimaPhysicsRigidBodyBullet.h"
#include "../include/AnimaPhysicsCollisionShapeBullet.h"

namespace AE
{
	namespace Physics
	{
		RigidBodyBullet::RigidBodyBullet(const AE::Physics::RigidBodyDesc &rigidBodyDesc) 
			: RigidBody(rigidBodyDesc), mRigidBody(0)
		{			
			mTransform.setIdentity();
			
			AE::Math::Vector3 position = rigidBodyDesc.sprite->getPosition();
			btVector3 btPosition = btVector3(position.x, position.y, position.z);
			mTransform.setOrigin(btPosition);
			
			AE::Math::Quaternion orientation = rigidBodyDesc.sprite->getOrientation();
			btQuaternion btRotation = btQuaternion(orientation.x, orientation.y, orientation.z, orientation.w);
			mTransform.setRotation(btRotation);

			mSprite = rigidBodyDesc.sprite;

			btVector3 localInertia(0,0,0);
			if(rigidBodyDesc.rigidBodyType == AE::Physics::RB_DYNAMIC)
				static_cast<AE::Physics::CollisionShapeBullet *>(rigidBodyDesc.collisionShape)->_getCollisionShape()->calculateLocalInertia(rigidBodyDesc.mass, localInertia);
			
			btRigidBody::btRigidBodyConstructionInfo rbInfo(rigidBodyDesc.mass, this, static_cast<AE::Physics::CollisionShapeBullet *>(rigidBodyDesc.collisionShape)->_getCollisionShape(), localInertia);
			mRigidBody = new btRigidBody(rbInfo);
		}

		RigidBodyBullet::~RigidBodyBullet()
		{
			if (mRigidBody && mRigidBody->getMotionState())
			{
				delete mRigidBody->getMotionState();
			}
			delete mRigidBody;
		}

		const AE::Math::Quaternion& RigidBodyBullet::getOrientation() 
		{
			btQuaternion quat = mRigidBody->getWorldTransform().getRotation();
			mOrientation.x = quat.getX();
			mOrientation.y = quat.getY();
			mOrientation.z = quat.getZ();
			mOrientation.w = quat.getW();
			return mOrientation; 
		}

		const AE::Math::Vector3& RigidBodyBullet::getPosition() 
		{ 
			btVector3 vec = mRigidBody->getWorldTransform().getOrigin();
			mPosition.x = vec.getX();
			mPosition.y = vec.getY();
			mPosition.z = vec.getZ();
			return mPosition; 
		}

		/*void RigidBodyBullet::setName(const std::string &name)
		{
			mName = name;
			//mNxActor->setName(name.c_str());
		}*/

		void RigidBodyBullet::setWorldTransform(const btTransform &worldTrans) 
		{
			if(NULL == mSprite) return; // silently return before we set a node

			mTransform = worldTrans;
			
			btQuaternion rot = worldTrans.getRotation();
			mSprite->setOrientation(rot.x(), rot.y(), rot.z(), rot.w());
			
			btVector3 pos = worldTrans.getOrigin();
			mSprite->setPosition(pos.x(), pos.y(), pos.z());
		}
	}
}