#ifndef __AE_PHYSICS2D_BODY_DESC__
#define __AE_PHYSICS2D_BODY_DESC__

#include "AnimaMathVector2.h"
#include "AnimaPhysics2dEnums.h"
#include "AnimaTypes.h"

namespace AE
{
	namespace Physics2d
	{
		class World;

		struct BodyDesc
		{
			AE::Real					angle;
			AE::Real					angularDamping;
			AE::Real					angularVelocity;
			AE::Physics2d::bodyType		bodyType;
			bool						ccd;
			AE::Real					density;
			AE::uint16					group;
			bool						isActive;
			bool						isAwake;
			bool						isTrigger;
			AE::Real					linearDamping;
			AE::Vector2					linearVelocity;
			AE::Real					mass;
			std::string					materialName;
			AE::Vector2					offset;
			AE::Quaternion				orientation;
			AE::Vector2					position;
			AE::Real					radius;
			AE::Vector2					scale;
			AE::Physics2d::ShapeType	shapeType;
			AE::Entity::Sprite			*sprite;
			AE::uint32					triggerFlag;

			BodyDesc()
			{
				bodyType = AE::Physics2d::BT_STATIC;
				ccd = false;
				density = 10.0;
				group = 0;
				isTrigger = false;
				mass = 0.0;
				materialName = "";
				offset = AE::Vector2::ZERO;
				orientation = AE::Quaternion::IDENTITY;
				position = AE::Vector2::ZERO;
				radius = 0.0;
				scale = AE::Vector2::UNIT_SCALE;
				shapeType = AE::Physics2d::ST_CIRCLE;
				triggerFlag = 0;
				world = 0;
			}

			~BodyDesc() { }
		};
	}
}

#endif