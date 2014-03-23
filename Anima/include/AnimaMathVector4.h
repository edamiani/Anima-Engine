#ifndef __ANIMA_MATH_VECTOR4__
#define __ANIMA_MATH_VECTOR4__

#include "AnimaTypes.h"

namespace AE
{
	namespace Math
	{
		class Vector4
		{
		public:
			float x, y, z, w;

			Vector4() { }
			Vector4(const Vector4 &vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) { }
			Vector4(float xValue, float yValue, float zValue, float wValue) : x(xValue), y(yValue), z(zValue), w(wValue) { }

			Vector4 &operator =(const Vector4 &vec) 
			{
				x = vec.x; y = vec.y; z = vec.z; w = vec.w;
				return *this;
			}

			bool operator ==(const Vector4 &vec) const 
			{
				return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
			}

			bool operator !=(const Vector4 &vec) const 
			{
				return x != vec.x || y != vec.y || z != vec.z || w != vec.w;
			}
		};
	}
}


#endif