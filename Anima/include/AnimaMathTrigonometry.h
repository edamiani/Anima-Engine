#ifndef __AE_MATH_TRIGONOMETRY__
#define __AE_MATH_TRIGONOMETRY__

#include "AnimaTypes.h"

#include <cmath>

namespace AE
{
	namespace Math
	{
		static const AE::Real PI = AE::Real(4.0 * atan(1.0));
		static const AE::Real TWO_PI = AE::Real(2.0 * PI);
		static const AE::Real HALF_PI = AE::Real(0.5 * PI);
		static const AE::Real PI_BY_2 = AE::Real(0.5 * PI);
		static const AE::Real PI_BY_3 = AE::Real((1 / 3.0) * PI);
		static const AE::Real PI_BY_4 = AE::Real(0.25 * PI);
		static const AE::Real PI_BY_6 = AE::Real((1 / 6.0) * PI);
	}
}

#endif