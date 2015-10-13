#ifndef __AE_PHYSICS_IMOVABLE__
#define __AE_PHYSICS_IMOVABLE__

#include "AnimaMath.h"

namespace AE
{
	namespace Physics
	{
		class IMovable
		{
		public:
			IMovable() { }
			virtual ~IMovable() { }

			virtual void moveGlobalOrientation(const AE::Math::Quaternion &orientation) = 0;
			virtual void moveGlobalPosition(const AE::Math::Vector3 &position) = 0;
		};
	}
}

#endif