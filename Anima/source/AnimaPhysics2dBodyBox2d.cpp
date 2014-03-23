@include "../include/AnimaPhysics2dBodyBox2d.h"

@include "../include/AnimaPhysics2dWorldBox2d.h"

#include "Box2d/Box2d.h"

#include <cassert>

namespace AE
{
	namespace Physics2d
	{
		BodyBox2d::BodyBox2d(const AE::Physics2d::BodyDesc &bodyDesc, AE::Physics2d::World *world)
		{
			b2BodyDef bodyDef;
			bodyDef.active = bodyDesc.isActive;
			bodyDef.angle = bodyDesc.angle;
			bodyDef.awake = bodyDesc.isAwake;
			bodyDef.bullet = bodyDesc.ccd;
			switch(bodyDesc.bodyType)
			{
			case AE::Physics2d::BT_DYNAMIC:
				bodyDef.type = b2_dynamicBody;
				break;

			case AE::Physics2d::BT_KINEMATIC:
				bodyDef.type = b2_kinematicBody;
				break;

			case AE::Physics2d::BT_STATIC:
				bodyDef.type = b2_staticBody;
				break;
			}
			bodyDef.linearDamping = bodyDesc.linearDamping;
			bodyDef.linearVelocity = b2Vec2(bodyDesc.linearVelocity.x, bodyDesc.linearVelocity.y);
			bodyDef.userData = static_cast<void *>(this);

			assert(bodyDesc.world);
			static_cast<AE::Physics2d::WorldBox2d *>()->_getBox2dWorld()->CreateBody(&bodyDef);
		}

		BodyBox2d::~BodyBox2d()
		{
			delete mBody;
		}
	}
}