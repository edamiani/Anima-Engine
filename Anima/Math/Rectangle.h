#ifndef __AE_MATH_RECTANGLE__
#define __AE_MATH_RECTANGLE__

#include "Anima/Types.h"

namespace AE
{
	namespace Math
	{
		struct Rectangle
		{
			Rectangle() : top(0), left(0), bottom(0), right(0) {}
			Rectangle(AE::int32 top, AE::int32 left, AE::int32 bottom, AE::int32 right) 
				: top(top), left(left), bottom(bottom), right(right) {}

			AE::int32 bottom;
			AE::int32 left;
			AE::int32 right;
			AE::int32 top;

			inline AE::Math::Rectangle operator = (const AE::Math::Rectangle &rhs)
			{
				top		= rhs.top;
				left	= rhs.left;
				bottom	= rhs.bottom;
				right	= rhs.right;

				return *this;
			}

			inline bool operator == (const AE::Math::Rectangle &rhs)
			{				
				return (top == rhs.top && left == rhs.left && bottom == rhs.bottom && right == rhs.right);
			}

			inline bool operator != (const AE::Math::Rectangle &rhs)
			{				
				return !(top == rhs.top && left == rhs.left && bottom == rhs.bottom && right == rhs.right);
			}
		};
	}
}

#endif