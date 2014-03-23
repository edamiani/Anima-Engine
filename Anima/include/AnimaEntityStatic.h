#ifndef __AE_ENTITY_STATIC__
#define __AE_ENTITY_STATIC__

#include "AnimaPrerequisites.h"
#include "AnimaPhysicsRigidBody.h"

namespace AE
{
	namespace Entity
	{
		class Static : public AE::Physics::RigidBody
		{
		public:
												Static() {  }
			virtual								~Static() {  }

			virtual const AE::AxisAlignedBox&	getBoundingBox() = 0;
			virtual AE::Real					getBoundingRadius() = 0;
			virtual std::string					getName() = 0;
			virtual AE::Quaternion				getOrientation() = 0;
			virtual AE::Vector3					getPosition() = 0;
			virtual AE::Physics::RigidBody*		getRigidBody() = 0;
			virtual AE::Vector3					getScale() = 0;
			virtual AE::Graphics::Sprite*		getSprite() = 0;
			virtual AE::Entity::Object3dType	getType() = 0;
			virtual void						setVisible(bool isVisible) = 0;
			virtual void						update(unsigned long timeSinceLastFrame) = 0;
		};
	}
}