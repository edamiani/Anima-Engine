#ifndef __AE_PHYSICS_RIGID_BODY__
#define __AE_PHYSICS_RIGID_BODY__

#include "AnimaPrerequisites.h"
#include "AnimaGraphicsSprite.h"
#include "AnimaPhysicsManager.h"

namespace AE
{
	namespace Physics
	{
		/*enum collisionNotify
		{
			CN_IGNORE_PAIR = 1,
			CN_START_TOUCH = 2,
			CN_TOUCH = 4,
			CN_END_TOUCH = 8
		};*/

		struct RigidBodyDesc
		{
			bool						ccd;
			AE::Physics::CollisionShape	*collisionShape;
			//AE::Real					density;
			//AE::uint16					group;
			//bool						isTrigger;
			AE::Real					mass;
			std::string					materialName;
			AE::Math::Vector3			offset;
			//AE::Real					radius;
			AE::Physics::RigidBodyType	rigidBodyType;
			AE::Graphics::Sprite		*sprite;
			//AE::uint32					triggerFlag;

			RigidBodyDesc()
			{
				ccd = false;
				collisionShape = 0;
				//density = 10.0;
				//group = 0;
				//isTrigger = false;
				mass = 0.0;
				materialName = "";
				offset = AE::Math::Vector3::ZERO;
				//radius = 0.0;
				rigidBodyType = AE::Physics::RB_STATIC;
				sprite = 0;
				//triggerFlag = 0;
			}

			~RigidBodyDesc() { }
		};

		class RigidBody
		{
		public:
			RigidBody() { }
			RigidBody(const AE::Physics::RigidBodyDesc &rigidBodyDesc)
			{ 
				mCollisionShape = rigidBodyDesc.collisionShape;
				//mDensity = rigidBodyDesc.density;
				//mGroup = rigidBodyDesc.group;
				mMass = rigidBodyDesc.mass;
				mMaterialName = rigidBodyDesc.materialName;
				mName = rigidBodyDesc.sprite->getName();
				mOffset = rigidBodyDesc.offset;
				mOrientation = rigidBodyDesc.sprite->getOrientation();
				mPosition = rigidBodyDesc.sprite->getPosition();
				//mScale = solidDesc.scale;
				//mTriggerFlag = solidDesc.triggerFlag;
				mRigidBodyType = rigidBodyDesc.rigidBodyType;
				//mSprite = rigidBodyDesc.sprite;
			}			
			virtual									~RigidBody() {  }

			//virtual AE::uint32						getTriggerFlag() = 0;
			const std::string&						getName() { return mName; }
			const virtual AE::Math::Quaternion&		getOrientation() = 0;
			const virtual AE::Math::Vector3&		getPosition() = 0;
			AE::Physics::RigidBodyType				getType() { return mRigidBodyType; }
			//virtual void							setName(const std::string &name) = 0;
			//virtual void							setSolidOffset(const AE::Math::Vector3 &offset) = 0;

		protected:
			AE::Physics::CollisionShape*	mCollisionShape;
			//AE::Real						mDensity;
			//short int						mGroup;
			std::string						mMaterialName;
			AE::Real						mMass;
			std::string						mName;
			AE::Math::Vector3				mOffset;
			AE::Math::Quaternion			mOrientation;
			AE::Math::Vector3				mPosition;
			//AE::Math::Vector3				mScale;
			//AE::uint32					mTriggerFlag;
			AE::Physics::RigidBodyType		mRigidBodyType;
			//AE::Graphics::Sprite*			mSprite;
		};
	}
}

#endif