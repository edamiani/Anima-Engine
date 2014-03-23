#ifndef __AE_MATH_POINT2__
#define __AE_MATH_POINT2__

#include "AnimaTypes.h"

namespace AE
{
	namespace Math
	{
		template<class T>
		struct Point2
		{
			Point2() : x(0), y(0) {}
			Point2(T xValue, T yValue) : x(xValue), y(yValue) {}

			T x;
			T y;

			inline AE::Math::Point2<T> operator + (const AE::Math::Point2<T> &rhs)
			{
				return AE::Math::Point2<T>(x + rhs.x, y + rhs.y);
			}

			inline AE::Math::Point2<T> operator - (const AE::Math::Point2<T> &rhs)
			{
				return AE::Math::Point2<T>(x - rhs.x, y - rhs.y);
			}

			inline AE::Math::Point2<T> operator * (const AE::Math::Point2<T> &rhs)
			{
				return AE::Math::Point2<T>(x * rhs.x, y * rhs.y);
			}

			inline AE::Math::Point2<T> operator = (const AE::Math::Point2<T> &rhs)
			{
				x = rhs.x;
				y = rhs.y;

				return *this;
			}

			inline bool operator != (const AE::Math::Point2<T> &rhs)
			{
				return !(x == rhs.x && y == rhs.y);
			}
		};
	}
}

#endif
