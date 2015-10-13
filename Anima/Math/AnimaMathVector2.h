#ifndef __AE_MATH_VECTOR2__
#define __AE_MATH_VECTOR2__

#include "../AnimaTypes.h"

#include <cmath>

namespace AE
{
	namespace Math
	{
		class Vector2
		{
		public:
			AE::Real x, y;

			Vector2() { }
			Vector2(const Vector2 &vec) : x(vec.x), y(vec.y) { }
			Vector2(AE::Real xValue, AE::Real yValue) : x(xValue), y(yValue) { }
			Vector2(AE::uint xValue, AE::uint yValue) : x(static_cast<AE::Real>(xValue)), y(static_cast<AE::Real>(yValue)) { }
			Vector2(AE::int16 xValue, AE::int16 yValue) : x(static_cast<AE::Real>(xValue)), y(static_cast<AE::Real>(yValue)) { }
			Vector2(AE::int32 xValue, AE::int32 yValue) : x(static_cast<AE::Real>(xValue)), y(static_cast<AE::Real>(yValue)) { }

			Vector2 &operator =(const Vector2 &vec) 
			{
				x = vec.x; y = vec.y;;
				return *this;
			}

			bool operator ==(const Vector2 &vec) const 
			{
				return x == vec.x && y == vec.y;
			}

			bool operator !=(const Vector2 &vec) const 
			{
				return x != vec.x || y != vec.y;
			}

			Vector2 operator -() const 
			{ 
				return Vector2(-x, -y); 
			}

			Vector2 operator +(const Vector2 &vec) const 
			{
				return Vector2(x + vec.x, y + vec.y);
			}

			Vector2 operator -(const Vector2 &vec) const 
			{
				return Vector2(x - vec.x, y - vec.y);
			}

			Vector2 operator *(AE::Real scalar) const 
			{
				return Vector2(x * scalar, y * scalar);
			}

			Vector2 operator * (const Vector2& rhs) const
			{
				return Vector2(x * rhs.x, y * rhs.y);
			}

			Vector2 operator /(AE::Real scalar) const 
			{
				float oneOverScalar = 1.0f / scalar; // NOTE: no check for divide by zero here
				return Vector2(x * oneOverScalar, y * oneOverScalar);
			}

			Vector2 &operator +=(const Vector2 &vec) 
			{
				x += vec.x; y += vec.y;
				return *this;
			}

			Vector2 &operator -=(const Vector2 &vec) 
			{
				x -= vec.x; y -= vec.y;
				return *this;
			}

			Vector2 &operator *=(AE::Real scalar) 
			{
				x *= scalar; y *= scalar;
				return *this;
			}

			Vector2 &operator /=(AE::Real scalar) 
			{
				float oneOverScalar = 1.0f / scalar;
				x *= oneOverScalar; y *= oneOverScalar;
				return *this;
			}

			// Function for writing to a stream.
			friend std::ostream& operator << (std::ostream& o, const Vector2& v)
			{
				o << "Vector2(" << v.x << ", " << v.y << ")";
				return o;
			}

			AE::Real magnitude() 
			{
				return sqrt(x*x + y*y);
			}

			inline void makeCeil(const Vector2& cmp)
			{
				if( cmp.x > x ) x = cmp.x;
				if( cmp.y > y ) y = cmp.y;
			}

			inline void makeFloor(const Vector2& cmp)
			{
				if( cmp.x < x ) x = cmp.x;
				if( cmp.y < y ) y = cmp.y;
			}

			void zero() { x = y = 0.0f; }

			static const Vector2 ZERO;
			static const Vector2 UNIT_X;
			static const Vector2 UNIT_Y;
			static const Vector2 NEGATIVE_UNIT_X;
			static const Vector2 NEGATIVE_UNIT_Y;
			static const Vector2 UNIT_SCALE;
		};
	}
}

#endif