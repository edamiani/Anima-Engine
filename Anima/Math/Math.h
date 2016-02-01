#ifndef __AE_MATH__
#define __AE_MATH__

#include "Anima/Types.h"

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

#include "Anima/Math/AxisAlignedBox.h"
#include "Anima/Math/Matrix4.h"
#include "Anima/Math/Point2.h"
#include "Anima/Math/Quaternion.h"
#include "Anima/Math/Vector2.h"
#include "Anima/Math/Vector3.h"
#include "Anima/Math/Vector4.h"

#endif
