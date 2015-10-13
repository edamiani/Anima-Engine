#ifndef __AE_MATH__
#define __AE_MATH__

#include "../AnimaTypes.h"

#include <cmath>
#include <limits>

namespace AE
{
	namespace Math
	{
		static inline AE::Real Abs(AE::Real value) { return AE::Real(fabs(value)); }

		static const AE::Real POS_INFINITY = std::numeric_limits<AE::Real>::infinity();
        static const AE::Real NEG_INFINITY = -std::numeric_limits<AE::Real>::infinity();
		static const AE::Real PI = AE::Real( 4.0 * atan( 1.0 ) );
		static const AE::Real TWO_PI = AE::Real( 2.0 * PI );
		static const AE::Real HALF_PI = AE::Real( 0.5 * PI );
	}
}

#include "AnimaMathAxisAlignedBox.h"
#include "AnimaMathMatrix4.h"
#include "AnimaMathPoint2.h"
#include "AnimaMathQuaternion.h"
#include "AnimaMathVector2.h"
#include "AnimaMathVector3.h"
#include "AnimaMathVector4.h"

#endif
