/*
-----------------------------------------------------------------------------
Module: AE::Physics2d

Class: Shape

Description: 2d shape description
-----------------------------------------------------------------------------
*/

#ifndef __AE_PHYSICS2D_SHAPE_DESC__
#define __AE_PHYSICS2D_SHAPE_DESC__

#include "AnimaMathVector2.h"

#include <vector>

namespace AE
{
	namespace Physics2d
	{
		struct ShapeDesc
		{
		public:
			ShapeDesc() { }

			std::vector<AE::Math::Vector2> points;
			AE::Real radius;
			AE::Physics2d::ShapeType shapeType;
		};
	}
}