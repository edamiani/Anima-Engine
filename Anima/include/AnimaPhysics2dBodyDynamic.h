#ifndef __AE_PHYSICS2D_BODY_DYNAMIC__
#define __AE_PHYSICS2D_BODY_DYNAMIC__

#include "AnimaPhysics2dBody.h"

#include "AnimaMathVector2.h"

namespace AE
{
	namespace Physics2d
	{
		class Dynamic : public AE::Physics2d::Body
		{
		public:
												Dynamic(const AE::Physics::SolidDesc &solidDesc) {  }
			virtual								~Dynamic() {  }

			virtual void						applyForce(const AE::Math::Vector2 &force, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) = 0;
			virtual void						applyForceAtLocalPos(const AE::Math::Vector2 &force, const AE::Math::Vector2 &position, AE::Physics2d::forceMode = AE::Physics2d::FM_FORCE) = 0;
			virtual void						applyTorque(const AE::Math::Vector2 &torque, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) = 0;
			virtual AE::Physics2d::Body*		getBody() = 0;
			virtual const AE::AxisAlignedBox&	getBoundingBox() = 0;
			virtual AE::Real					getBoundingRadius() = 0;
			virtual std::string					getName() = 0;
			virtual AE::Quaternion				getOrientation() = 0;
			virtual AE::Math::Vector2			getPosition() = 0;
			virtual AE::Math::Vector2			getScale() = 0;
			virtual AE::Entity::Sprite*			getSprite() = 0;
			virtual AE::Entity::Object3dType	getType() = 0;
			virtual void						moveGlobalPosition(const AE::Math::Vector2 &position) = 0;
			virtual void						setAngularVelocity(const AE::Math::Vector2 &velocity) = 0;
			virtual void						setLinearVelocity(const AE::Math::Vector2 &velocity) = 0;
			virtual void						setVisible(bool isVisible) = 0;
			virtual void						update(unsigned long timeSinceLastFrame) = 0;
		};
	}
}

#endif