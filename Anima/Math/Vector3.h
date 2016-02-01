#ifndef __AE_MATH_VECTOR3__
#define __AE_MATH_VECTOR3__

#include "Anima/Types.h"

#include <cmath>

namespace AE
{
	namespace Math
	{
		class Vector3
		{
		public:
			float x, y, z;

			Vector3() { }
			Vector3(const Vector3 &vec) : x(vec.x), y(vec.y), z(vec.z) { }
			Vector3(float xValue, float yValue, float zValue) : x(xValue), y(yValue), z(zValue) { }

			Vector3 &operator =(const Vector3 &vec) 
			{
				x = vec.x; y = vec.y; z = vec.z;
				return *this;
			}

			bool operator ==(const Vector3 &vec) const 
			{
				return x == vec.x && y == vec.y && z == vec.z;
			}

			bool operator !=(const Vector3 &vec) const 
			{
				return x != vec.x || y != vec.y || z != vec.z;
			}

			Vector3 operator -() const 
			{ 
				return Vector3(-x, -y, -z); 
			}

			Vector3 operator +(const Vector3 &vec) const 
			{
				return Vector3(x + vec.x, y + vec.y, z + vec.z);
			}

			Vector3 operator -(const Vector3 &vec) const 
			{
				return Vector3(x - vec.x, y - vec.y, z - vec.z);
			}

			Vector3 operator *(float scalar) const 
			{
				return Vector3(x * scalar, y * scalar, z * scalar);
			}

			Vector3 operator * (const Vector3& rhs) const
			{
				return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
			}

			Vector3 operator /(float scalar) const 
			{
				float oneOverScalar = 1.0f / scalar; // NOTE: no check for divide by zero here
				return Vector3(x * oneOverScalar, y * oneOverScalar, z * oneOverScalar);
			}

			Vector3 &operator +=(const Vector3 &vec) 
			{
				x += vec.x; y += vec.y; z += vec.z;
				return *this;
			}

			Vector3 &operator -=(const Vector3 &vec) 
			{
				x -= vec.x; y -= vec.y; z -= vec.z;
				return *this;
			}

			Vector3 &operator *=(float scalar) 
			{
				x *= scalar; y *= scalar; z *= scalar;
				return *this;
			}

			Vector3 &operator /=(float scalar) 
			{
				float oneOverScalar = 1.0f / scalar;
				x *= oneOverScalar; y *= oneOverScalar; z *= oneOverScalar;
				return *this;
			}

			// Function for writing to a stream.
			friend std::ostream& operator << (std::ostream& o, const Vector3& v)
			{
				o << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
				return o;
			}

			Vector3 cross(const Vector3 &vec) 
			{
				return Vector3(
					(y * vec.z) - (z * vec.y),
					(z * vec.x) - (x * vec.z),
					(x * vec.y) - (y * vec.x)
				);
			}

			float dot(const Vector3 &vec) const 
			{
				return (x * vec.x) + (y * vec.y) + (z * vec.z);
			}

			float magnitude() 
			{
				return sqrt(x*x + y*y + z*z);
			}

			inline void makeCeil(const Vector3& cmp)
			{
				if( cmp.x > x ) x = cmp.x;
				if( cmp.y > y ) y = cmp.y;
				if( cmp.z > z ) z = cmp.z;
			}

			inline void makeFloor(const Vector3& cmp)
			{
				if( cmp.x < x ) x = cmp.x;
				if( cmp.y < y ) y = cmp.y;
				if( cmp.z < z ) z = cmp.z;
			}

			void normalize() 
			{
				float magnitudeSquared = x*x + y*y + z*z;
				if (magnitudeSquared > 0.0f) 
				{ // check for divide-by-zero
					float oneOverMagnitude = 1.0f / sqrt(magnitudeSquared);
					x *= oneOverMagnitude;
					y *= oneOverMagnitude;
					z *= oneOverMagnitude;
				}
			}

			void zero() { x = y = z = 0.0f; }

			static const Vector3 ZERO;
			static const Vector3 UNIT_X;
			static const Vector3 UNIT_Y;
			static const Vector3 UNIT_Z;
			static const Vector3 NEGATIVE_UNIT_X;
			static const Vector3 NEGATIVE_UNIT_Y;
			static const Vector3 NEGATIVE_UNIT_Z;
			static const Vector3 UNIT_SCALE;
		};
	}
}


#endif