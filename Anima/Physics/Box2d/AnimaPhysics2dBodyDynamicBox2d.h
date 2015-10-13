#ifndef __AE_PHYSICS2D_BODY_DYNAMIC_BOX2D__
#define __AE_PHYSICS2D_BODY_DYNAMIC_BOX2D__

#include "AnimaPhysics2dBodyBox2d.h"
#include "AnimaPhysics2dBodyDynamic.h"

#include "AnimaPhysics2dBodyDesc.h"

class b2Body;

namespace AE
{
	namespace Physics2d
	{
		class BodyDynamicBox2d : public AE::Physics2d::BodyBox2d, public AE::Physics2d::BodyDynamic
		{
		public:
									BodyBox2d(const AE::Physics2d::BodyDesc &bodyDesc);			
									~BodyBox2d();

			/***** Inherited from AE::Physics2d::BodyDynamic *****/
			void					applyForce(const AE::Vector2 &force, AE::Physics2d::ForceMode mode = FM_FORCE);
			void					applyForceAtLocalPos(const AE::Vector2 &force, const AE::Math::Vector2 &position, AE::Physics2d::ForceMode mode = FM_FORCE);
			void					applyTorque(const AE::Vector2 &torque, AE::Physics2d::ForceMode mode = FM_FORCE);
			AE::Real				getAngle();
			AE::Real				getAngularDamping();
			AE::Math::Vector2		getAngularVelocity();
			AE::Real				getInertia();
			AE::Real				getLinearDamping();
			AE::Real				getLinearVelocity();
			AE::Real				getMass();
			AE::Vector2				getPosition();
			bool					isActive();
			bool					isAwake();
			void					moveGlobalOrientation(const AE::Quaternion &orientation);
			void					moveGlobalPosition(const AE::Vector2 &position);
			void					setAngle();
			void					setAngularVelocity(const AE::Vector2 &velocity);
			void					setLinearVelocity(const AE::Vector2 &velocity);
			void					setName(std::string name);
			void					setSolidOffset(const AE::Vector2 &offset);

			/***** Inherited from AE::Physics2d::Body
			AE::Physics2d::bodyType	getType();
			*****/
		};
	}
}

#endif