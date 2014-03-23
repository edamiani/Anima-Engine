#ifndef __AE_MATH_MATRIX4__
#define __AE_MATH_MATRIX4__

#include "AnimaTypes.h"

#include "AnimaMathVector4.h"

#include <cassert>

namespace AE
{
	namespace Math
	{
		class Matrix4
		{
		public:
			inline Matrix4()
			{
			}

			inline Matrix4(
				AE::Real m00, AE::Real m01, AE::Real m02, AE::Real m03,
				AE::Real m10, AE::Real m11, AE::Real m12, AE::Real m13,
				AE::Real m20, AE::Real m21, AE::Real m22, AE::Real m23,
				AE::Real m30, AE::Real m31, AE::Real m32, AE::Real m33 )
			{
				m[0][0] = m00;
				m[0][1] = m01;
				m[0][2] = m02;
				m[0][3] = m03;
				m[1][0] = m10;
				m[1][1] = m11;
				m[1][2] = m12;
				m[1][3] = m13;
				m[2][0] = m20;
				m[2][1] = m21;
				m[2][2] = m22;
				m[2][3] = m23;
				m[3][0] = m30;
				m[3][1] = m31;
				m[3][2] = m32;
				m[3][3] = m33;
			}

			inline Matrix4(AE::Math::Matrix4 const &matrix)
			{
				m[0][0] = matrix[0][0];
				m[0][1] = matrix[0][1];
				m[0][2] = matrix[0][2];
				m[0][3] = matrix[0][3];
				m[1][0] = matrix[1][0];
				m[1][1] = matrix[1][1];
				m[1][2] = matrix[1][2];
				m[1][3] = matrix[1][3];
				m[2][0] = matrix[2][0];
				m[2][1] = matrix[2][1];
				m[2][2] = matrix[2][2];
				m[2][3] = matrix[2][3];
				m[3][0] = matrix[3][0];
				m[3][1] = matrix[3][1];
				m[3][2] = matrix[3][2];
				m[3][3] = matrix[3][3];
			}

			inline AE::Real* operator [] (size_t row)
			{
				assert(row < 4);
				return m[row];
			}

			inline AE::Real const * const operator [] (size_t row) const
			{
				assert(row < 4);
				return m[row];
			}

			inline Matrix4 add(Matrix4 const &m2)
			{
				Matrix4 temp;
				temp.m[0][0] = m[0][0] + m2[0][0];
				temp.m[0][1] = m[0][1] + m2[0][1];
				temp.m[0][2] = m[0][2] + m2[0][2];
				temp.m[0][3] = m[0][3] + m2[0][3];

				temp.m[1][0] = m[1][0] + m2[1][0];
				temp.m[1][1] = m[1][1] + m2[1][1];
				temp.m[1][2] = m[1][2] + m2[1][2];
				temp.m[1][3] = m[1][3] + m2[1][3];

				temp.m[2][0] = m[2][0] + m2[2][0];
				temp.m[2][1] = m[2][1] + m2[2][1];
				temp.m[2][2] = m[2][2] + m2[2][2];
				temp.m[2][3] = m[2][3] + m2[2][3];

				temp.m[3][0] = m[3][0] + m2[3][0];
				temp.m[3][1] = m[3][1] + m2[3][1];
				temp.m[3][2] = m[3][2] + m2[3][2];
				temp.m[3][3] = m[3][3] + m2[3][3];

				return temp;
			}

			Matrix4 Matrix4::inverse() const
			{
				AE::Real m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
				AE::Real m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
				AE::Real m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
				AE::Real m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

				AE::Real v0 = m20 * m31 - m21 * m30;
				AE::Real v1 = m20 * m32 - m22 * m30;
				AE::Real v2 = m20 * m33 - m23 * m30;
				AE::Real v3 = m21 * m32 - m22 * m31;
				AE::Real v4 = m21 * m33 - m23 * m31;
				AE::Real v5 = m22 * m33 - m23 * m32;

				AE::Real t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
				AE::Real t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
				AE::Real t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
				AE::Real t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

				AE::Real invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

				AE::Real d00 = t00 * invDet;
				AE::Real d10 = t10 * invDet;
				AE::Real d20 = t20 * invDet;
				AE::Real d30 = t30 * invDet;

				AE::Real d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
				AE::Real d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
				AE::Real d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
				AE::Real d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

				v0 = m10 * m31 - m11 * m30;
				v1 = m10 * m32 - m12 * m30;
				v2 = m10 * m33 - m13 * m30;
				v3 = m11 * m32 - m12 * m31;
				v4 = m11 * m33 - m13 * m31;
				v5 = m12 * m33 - m13 * m32;

				Real d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
				Real d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
				Real d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
				Real d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

				v0 = m21 * m10 - m20 * m11;
				v1 = m22 * m10 - m20 * m12;
				v2 = m23 * m10 - m20 * m13;
				v3 = m22 * m11 - m21 * m12;
				v4 = m23 * m11 - m21 * m13;
				v5 = m23 * m12 - m22 * m13;

				Real d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
				Real d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
				Real d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
				Real d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

				return Matrix4(
					d00, d01, d02, d03,
					d10, d11, d12, d13,
					d20, d21, d22, d23,
					d30, d31, d32, d33);
			}

			inline Matrix4 multiply(Matrix4 const &m2) const
			{
				Matrix4 temp;
				temp.m[0][0] = m[0][0] * m2[0][0] + m[0][1] * m2[1][0] + m[0][2] * m2[2][0] + m[0][3] * m2[3][0];
				temp.m[0][1] = m[0][0] * m2[0][1] + m[0][1] * m2[1][1] + m[0][2] * m2[2][1] + m[0][3] * m2[3][1];
				temp.m[0][2] = m[0][0] * m2[0][2] + m[0][1] * m2[1][2] + m[0][2] * m2[2][2] + m[0][3] * m2[3][2];
				temp.m[0][3] = m[0][0] * m2[0][3] + m[0][1] * m2[1][3] + m[0][2] * m2[2][3] + m[0][3] * m2[3][3];

				temp.m[1][0] = m[1][0] * m2[0][0] + m[1][1] * m2[1][0] + m[1][2] * m2[2][0] + m[1][3] * m2[3][0];
				temp.m[1][1] = m[1][0] * m2[0][1] + m[1][1] * m2[1][1] + m[1][2] * m2[2][1] + m[1][3] * m2[3][1];
				temp.m[1][2] = m[1][0] * m2[0][2] + m[1][1] * m2[1][2] + m[1][2] * m2[2][2] + m[1][3] * m2[3][2];
				temp.m[1][3] = m[1][0] * m2[0][3] + m[1][1] * m2[1][3] + m[1][2] * m2[2][3] + m[1][3] * m2[3][3];

				temp.m[2][0] = m[2][0] * m2[0][0] + m[2][1] * m2[1][0] + m[2][2] * m2[2][0] + m[2][3] * m2[3][0];
				temp.m[2][1] = m[2][0] * m2[0][1] + m[2][1] * m2[1][1] + m[2][2] * m2[2][1] + m[2][3] * m2[3][1];
				temp.m[2][2] = m[2][0] * m2[0][2] + m[2][1] * m2[1][2] + m[2][2] * m2[2][2] + m[2][3] * m2[3][2];
				temp.m[2][3] = m[2][0] * m2[0][3] + m[2][1] * m2[1][3] + m[2][2] * m2[2][3] + m[2][3] * m2[3][3];

				temp.m[3][0] = m[3][0] * m2[0][0] + m[3][1] * m2[1][0] + m[3][2] * m2[2][0] + m[3][3] * m2[3][0];
				temp.m[3][1] = m[3][0] * m2[0][1] + m[3][1] * m2[1][1] + m[3][2] * m2[2][1] + m[3][3] * m2[3][1];
				temp.m[3][2] = m[3][0] * m2[0][2] + m[3][1] * m2[1][2] + m[3][2] * m2[2][2] + m[3][3] * m2[3][2];
				temp.m[3][3] = m[3][0] * m2[0][3] + m[3][1] * m2[1][3] + m[3][2] * m2[2][3] + m[3][3] * m2[3][3];

				return temp;
			}

			inline AE::Math::Vector4 multiply(AE::Math::Vector4 const &v) const
			{
				AE::Math::Vector4 temp;
				temp.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3] * v.w;
				temp.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3] * v.w;
				temp.z = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3] * v.w;
				temp.w = m[3][0] * v.x + m[3][1] * v.y + m[3][2] * v.z + m[3][3] * v.w;

				return temp;
			}

			inline Matrix4 operator * (Matrix4 const &m2) const
			{
				return multiply(m2);
			}

			inline void setIdentity()
			{
				m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
				m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
				m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
				m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
			}

			inline Matrix4 subtract(Matrix4 const &m2)
			{
				Matrix4 temp;
				temp.m[0][0] = m[0][0] - m2[0][0];
				temp.m[0][1] = m[0][1] - m2[0][1];
				temp.m[0][2] = m[0][2] - m2[0][2];
				temp.m[0][3] = m[0][3] - m2[0][3];

				temp.m[1][0] = m[1][0] - m2[1][0];
				temp.m[1][1] = m[1][1] - m2[1][1];
				temp.m[1][2] = m[1][2] - m2[1][2];
				temp.m[1][3] = m[1][3] - m2[1][3];

				temp.m[2][0] = m[2][0] - m2[2][0];
				temp.m[2][1] = m[2][1] - m2[2][1];
				temp.m[2][2] = m[2][2] - m2[2][2];
				temp.m[2][3] = m[2][3] - m2[2][3];

				temp.m[3][0] = m[3][0] - m2[3][0];
				temp.m[3][1] = m[3][1] - m2[3][1];
				temp.m[3][2] = m[3][2] - m2[3][2];
				temp.m[3][3] = m[3][3] - m2[3][3];

				return temp;
			}

			inline Matrix4 transpose()
			{
				return Matrix4(m[0][0], m[1][0], m[2][0], m[3][0],
							   m[0][1], m[1][1], m[2][1], m[3][1],
							   m[0][2], m[1][2], m[2][2], m[3][2],
							   m[0][3], m[1][3], m[2][3], m[3][3]);
			}

			union
			{
				AE::Real m[4][4];
				AE::Real _m[16];
			};

		private:

		};
	}
}

#endif
