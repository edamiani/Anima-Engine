#ifndef __AE_MATH_MATRIX3__
#define __AE_MATH_MATRIX3__

#include "Anima/Types.h"

#include <cassert>

namespace AE
{
	namespace Math
	{
		class Matrix3
		{
		public:
			inline Matrix3()
			{
			}

			inline Matrix3(
				AE::Real m00, AE::Real m01, AE::Real m02,
				AE::Real m10, AE::Real m11, AE::Real m12,
				AE::Real m20, AE::Real m21, AE::Real m22 )
			{
				m[0][0] = m00;
				m[0][1] = m01;
				m[0][2] = m02;
				m[1][0] = m10;
				m[1][1] = m11;
				m[1][2] = m12;
				m[2][0] = m20;
				m[2][1] = m21;
				m[2][2] = m22;
			}

			inline AE::Real* operator [] (size_t row)
			{
				assert(row < 3);
				return m[row];
			}

			inline const AE::Real* const operator [] (size_t row) const
			{
				assert(row < 3);
				return m[row];
			}

			inline Matrix3 add(const Matrix3 &m2)
			{
				Matrix3 temp;
				temp.m[0][0] = m[0][0] + m2[0][0];
				temp.m[0][1] = m[0][1] + m2[0][1];
				temp.m[0][2] = m[0][2] + m2[0][2];

				temp.m[1][0] = m[1][0] + m2[1][0];
				temp.m[1][1] = m[1][1] + m2[1][1];
				temp.m[1][2] = m[1][2] + m2[1][2];

				temp.m[2][0] = m[2][0] + m2[2][0];
				temp.m[2][1] = m[2][1] + m2[2][1];
				temp.m[2][2] = m[2][2] + m2[2][2];

				return temp;
			}

			inline Matrix3 multiply(const Matrix3 &m2) const
			{
				Matrix3 temp;
				temp.m[0][0] = m[0][0] * m2[0][0] + m[0][1] * m2[1][0] + m[0][2] * m2[2][0];
				temp.m[0][1] = m[0][0] * m2[0][1] + m[0][1] * m2[1][1] + m[0][2] * m2[2][1];
				temp.m[0][2] = m[0][0] * m2[0][2] + m[0][1] * m2[1][2] + m[0][2] * m2[2][2];

				temp.m[1][0] = m[1][0] * m2[0][0] + m[1][1] * m2[1][0] + m[1][2] * m2[2][0];
				temp.m[1][1] = m[1][0] * m2[0][1] + m[1][1] * m2[1][1] + m[1][2] * m2[2][1];
				temp.m[1][2] = m[1][0] * m2[0][2] + m[1][1] * m2[1][2] + m[1][2] * m2[2][2];

				temp.m[2][0] = m[2][0] * m2[0][0] + m[2][1] * m2[1][0] + m[2][2] * m2[2][0];
				temp.m[2][1] = m[2][0] * m2[0][1] + m[2][1] * m2[1][1] + m[2][2] * m2[2][1];
				temp.m[2][2] = m[2][0] * m2[0][2] + m[2][1] * m2[1][2] + m[2][2] * m2[2][2];

				return temp;
			}

			inline Matrix3 operator * (const Matrix3 &m2) const
			{
				return multiply(m2);
			}

			inline void setIdentity()
			{
				m[0][0] = 1; m[0][1] = 0; m[0][2] = 0;
				m[1][0] = 0; m[1][1] = 1; m[1][2] = 0;
				m[2][0] = 0; m[2][1] = 0; m[2][2] = 1;
			}

			inline Matrix3 subtract(const Matrix3 &m2)
			{
				Matrix3 temp;
				temp.m[0][0] = m[0][0] - m2[0][0];
				temp.m[0][1] = m[0][1] - m2[0][1];
				temp.m[0][2] = m[0][2] - m2[0][2];

				temp.m[1][0] = m[1][0] - m2[1][0];
				temp.m[1][1] = m[1][1] - m2[1][1];
				temp.m[1][2] = m[1][2] - m2[1][2];

				temp.m[2][0] = m[2][0] - m2[2][0];
				temp.m[2][1] = m[2][1] - m2[2][1];
				temp.m[2][2] = m[2][2] - m2[2][2];

				return temp;
			}

			inline Matrix3 transpose()
			{
				return Matrix3(m[0][0], m[1][0], m[2][0],
							   m[0][1], m[1][1], m[2][1],
							   m[0][2], m[1][2], m[2][2]);
			}

			union
			{
				AE::Real m[3][3];
				AE::Real _m[9];
			};

		private:

		};
	}
}

#endif
