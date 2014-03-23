#ifndef __AE_PHYSICS_RIGID_BODY_BULLET__
#define __AE_PHYSICS_RIGID_BODY_BULLET__

#include "AnimaPhysicsRigidBody.h"
#include "AnimaPhysicsManagerBullet.h"

namespace AE
{
	namespace Physics
	{
		class RigidBodyBullet : public AE::Physics::RigidBody, public btMotionState
		{
		public:
										RigidBodyBullet(const AE::Physics::RigidBodyDesc &rigidBodyDesc);
										~RigidBodyBullet();

			//AE::uint32				getTriggerFlag() { return mTriggerFlag; }
			const AE::Math::Quaternion&	getOrientation();
			const AE::Math::Vector3&	getPosition();
			//void						setName(const std::string &name);
			void						setSolidOffset(const AE::Math::Vector3 &offset) { mOffset = offset; }
			
			// btMotionState callbacks
			virtual void				getWorldTransform(btTransform &worldTrans) const { worldTrans = mTransform; }			
			virtual void				setWorldTransform(const btTransform &worldTrans);

			btRigidBody*				_getRigidBody() { return mRigidBody; }

		private:
			btRigidBody*					mRigidBody;
			AE::Graphics::Sprite*			mSprite;
			btTransform						mTransform;
		};
	}
}

#endif