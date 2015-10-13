#ifndef __AE_PHYSICS2D_BODY__
#define __AE_PHYSICS2D_BODY__

#include "AnimaPhysics2dBodyDesc.h"

namespace AE
{
	namespace Physics2d
	{
		class Body
		{
		public:
										Body(const AE::Physics::SolidDesc &solidDesc);			
			virtual						~Body();

			virtual void				applyForce(const AE::Vector2 &force, AE::Physics::forceMode mode = FM_FORCE) = 0;
			virtual void				applyForceAtLocalPos(const AE::Vector2 &force, const AE::Vector2 &position, AE::Physics::forceMode mode = FM_FORCE) = 0;
			virtual void				applyTorque(const AE::Vector2 &torque, AE::Physics::forceMode mode = FM_FORCE) = 0;
			virtual std::string			getName() = 0;
			virtual AE::Quaternion		getOrientation() = 0;
			virtual AE::Vector2			getPosition() = 0;
			AE::Physics2d::bodyType		getType() { return mBodyType; }
			virtual void				moveGlobalOrientation(const AE::Quaternion &orientation) = 0;
			virtual void				moveGlobalPosition(const AE::Vector2 &position) = 0;
			virtual void				setAngularVelocity(const AE::Vector2 &velocity) = 0;
			virtual void				setLinearVelocity(const AE::Vector2 &velocity) = 0;
			virtual void				setName(std::string name) = 0;
			virtual void				setSolidOffset(const AE::Vector2 &offset) = 0;

		protected:
			AE::Physics2d::BodyType		mBodyType;
		};
	}
}

#endif