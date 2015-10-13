#ifndef __AE_PHYSICS2D_BODY_KINEMATIC_BOX2D__
#define __AE_PHYSICS2D_BODY_KINEMATIC_BOX2D__

#include "AnimaPhysics2dBodyBox2d.h"
#include "AnimaPhysics2dBodyKinematic.h"

#include "AnimaPhysics2dBodyDesc.h"

class b2Body;

namespace AE
{
	namespace Physics2d
	{
		class BodyKinematicBox2d : public AE::Physics2d::BodyBox2d, public AE::Physics2d::BodyKinematic
		{
		public:
												BodyKinematicBox2d(const AE::Physics2d::BodyDesc &bodyDesc);			
												~BodyKinematicBox2d();

			virtual const AE::AxisAlignedBox&	getBoundingBox() = 0;
			virtual AE::Real					getBoundingRadius() = 0;
			virtual AE::uint32					getId() = 0;
			virtual std::string					getName() = 0;
			virtual AE::Scene::Node*			getNode() = 0;
			virtual AE::Quaternion				getOrientation() = 0;
			virtual AE::Math::Vector2			getPosition() = 0;
			virtual AE::Math::Vector2			getScale() = 0;
			virtual AE::Physics2d::Solid*		getSolid() = 0;
			virtual AE::Entity::Sprite*			getSprite() = 0;
			virtual AE::Entity::Object3dType	getType() = 0;
			virtual void						moveGlobalPosition(const AE::Math::Vector2 &position) = 0;
			virtual void						moveGlobalOrientation(const AE::Quaternion &orientation) = 0;
			virtual void						setVisible(bool isVisible) = 0;
			virtual void						update(unsigned long timeSinceLastFrame) = 0;
		};
	}
}

#endif