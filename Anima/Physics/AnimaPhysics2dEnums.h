#ifndef __AE_PHYSICS2D_ENUMS__
#define __AE_PHYSICS2D_ENUMS__

#include "AnimaEnums.h"

namespace AE
{
	namespace Physics2d
	{
		enum BodyType
		{
			BT_CHARACTER = 1,
			BT_DYNAMIC,
			BT_KINEMATIC,
			BT_STATIC,
			BT_TRIGGER
		};

		enum CollisionNotify
		{
			CN_IGNORE_PAIR = 1,
			CN_START_TOUCH = 2,
			CN_TOUCH = 4,
			CN_END_TOUCH = 8
		};

		enum ForceMode
		{
			FM_ACCELERATION,
			FM_FORCE,
			FM_IMPULSE,
			FM_SMOOTH_IMPULSE,
			FM_SMOOTH_VELOCITY_CHANGE,
			FM_VELOCITY_CHANGE
		};

		enum JointType
		{
			JT_BALLANDSOCKET = 1,
			JT_HINGE,
			JT_SLIDER,
			JT_UNIVERSAL,
			JT_WHEEL,
			JT_FIXED
		};

		enum ShapeType
		{
			ST_CHAIN,
			ST_CIRCLE,
			ST_EDGE,
			ST_POLYGON
		};
	}
}