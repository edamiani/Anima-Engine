#ifndef __AE_PHYSICS_IPUSHABLE__
#define __AE_PHYSICS_IPUSHABLE__

#include "AnimaMath.h"

namespace AE
{
	namespace Physics
	{
		enum forceMode
		{
			FM_ACCELERATION,
			FM_FORCE,
			FM_IMPULSE,
			FM_SMOOTH_IMPULSE,
			FM_SMOOTH_VELOCITY_CHANGE,
			FM_VELOCITY_CHANGE
		};

		class IPushable
		{
		public:
			IPushable() { }
			virtual ~IPushable() { }

			virtual void applyForce(const AE::Math::Vector3 &force, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) = 0;
			virtual void applyForceAtLocalPos(const AE::Math::Vector3 &force, const AE::Math::Vector3 &position, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) = 0;
			virtual void applyTorque(const AE::Math::Vector3 &torque, AE::Physics::forceMode mode = AE::Physics::FM_FORCE) = 0;
			virtual void setAngularVelocity(const AE::Math::Vector3 &velocity) = 0;
			virtual void setLinearVelocity(const AE::Math::Vector3 &velocity) = 0;
		};
	}
}

#endif