#ifndef __AE_ENTITY_KINEMATIC__
#define __AE_ENTITY_KINEMATIC__

#include "AnimaPrerequisites.h"
#include "AnimaPhysicsRigidBody.h"
#include "AnimaPhysicsIMovable.h"

namespace AE
{
	namespace Entity
	{
		class Kinematic : public AE::Physics::IMovable
		{
		public:
										Kinematic() : mSprite(0), mRigidBody(0) {  }
										Kinematic(AE::Graphics::Sprite *sprite, AE::Physics::RigidBody *rigidBody) : mSprite(sprite), mRigidBody(rigidBody) {  }
										~Kinematic() {  }

			/*const AE::AxisAlignedBox&	getBoundingBox() = 0;
			AE::Real					getBoundingRadius() = 0;
			std::string					getName() = 0;
			AE::Quaternion				getOrientation() = 0;
			AE::Vector3					getPosition() = 0;
			AE::Physics::RigidBody*		getRigidBody() = 0;
			AE::Vector3					getScale() = 0;
			AE::Graphics::Sprite*		getSprite() = 0;
			AE::Entity::Object3dType	getType() = 0;*/
			void						moveGlobalOrientation(const AE::Math::Quaternion &orientation) {}
			void						moveGlobalPosition(const AE::Math::Vector3 &position) {}
			//void						setVisible(bool isVisible) = 0;
			//void						update(unsigned long timeSinceLastFrame) = 0;

		protected:
			AE::Graphics::Sprite		*mSprite;
			AE::Physics::RigidBody		*mRigidBody;
		};
	}
}

#endif