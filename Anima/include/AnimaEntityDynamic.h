#ifndef __AE_ENTITY_DYNAMIC__
#define __AE_ENTITY_DYNAMIC__

#include "AnimaPrerequisites.h"
#include "AnimaPhysicsRigidBody.h"
#include "AnimaPhysicsIPushable.h"

namespace AE
{
	namespace Entity
	{
		class Dynamic : public AE::Physics::IPushable
		{
		public:
										Dynamic() : mSprite(0), mRigidBody(0) {  }
										Dynamic(AE::Graphics::Sprite *sprite, AE::Physics::RigidBody *rigidBody) : mSprite(sprite), mRigidBody(rigidBody) {  }
										~Dynamic() {  }

			void						applyForce(const AE::Math::Vector3 &force, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) { }
			void						applyForceAtLocalPos(const AE::Math::Vector3 &force, const AE::Math::Vector3 &position, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) { }
			void						applyTorque(const AE::Math::Vector3 &torque, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) { }
			/*const AE::AxisAlignedBox&	getBoundingBox() { }
			AE::Real					getBoundingRadius() { }
			std::string					getName() { }
			AE::Quaternion				getOrientation() { }
			AE::Vector3					getPosition() { }
			AE::Physics::RigidBody*		getRigidBody() { }
			AE::Vector3					getScale() { }
			AE::Graphics::Sprite*		getSprite() { }
			AE::Entity::Object3dType	getType() { }*/
			void						setAngularVelocity(const AE::Math::Vector3 &velocity) {}
			void						setLinearVelocity(const AE::Math::Vector3 &velocity) { }
			//void						setVisible(bool isVisible) { }
			//void						update(unsigned long timeSinceLastFrame) { }

		protected:
			AE::Graphics::Sprite		*mSprite;
			AE::Physics::RigidBody		*mRigidBody;
		};
	}
}

#endif