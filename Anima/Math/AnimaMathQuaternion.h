#ifndef __ANIMA_MATH_QUATERNION__
#define __ANIMA_MATH_QUATERNION__

#include "../AnimaTypes.h"

namespace AE
{
	namespace Math
	{
		class Quaternion
		{
		public:
			AE::Real x, y, z, w;

			Quaternion (AE::Real fX = 0.0, AE::Real fY = 0.0, AE::Real fZ = 0.0, AE::Real fW = 1.0)
			{
				x = fX; y = fY; z = fZ; w = fW;
			}

			~Quaternion() { }

			static const Quaternion ZERO;
			static const Quaternion IDENTITY; 
		};
	}
}

#endif