#ifndef __AE_PHYSICS2D_BODY_STATIC__
#define __AE_PHYSICS2D_BODY_STATIC__

#include "AnimaPhysics2dBody.h"

#include "AnimaMathVector2.h"

namespace AE
{
	namespace Physics2d
	{
		class Static : public AE::Physics2d::Body
		{
		public:
												Static(const AE::Physics::SolidDesc &solidDesc) {  }
			virtual								~Static() {  }

			virtual const AE::AxisAlignedBox&	getBoundingBox() = 0;
			virtual AE::Real					getBoundingRadius() = 0;
			virtual std::string					getName() = 0;
			virtual AE::Quaternion				getOrientation() = 0;
			virtual AE::Math::Vector2			getPosition() = 0;
			virtual AE::Math::Vector2			getScale() = 0;
			virtual AE::Physics2d::Solid*		getSolid() = 0;
			virtual AE::Entity::Sprite*			getSprite() = 0;
			virtual AE::Entity::Object3dType	getType() = 0;
			virtual void						setVisible(bool isVisible) = 0;
		};
	}
}

#endif