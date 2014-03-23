#include "../include/AnimaPhysics2dBodyDynamicBox2d.h"

namespace AE
{
	namespace Physics2d
	{
		BodyDynamicBox2d::BodyDynamicBox2d(const AE::Physics2d::BodyDesc &bodyDesc)
			: BodyBox2d(bodyDesc)
		{
		}

		BodyDynamicBox2d::~BodyDynamicBox2d()
		{
		}
	}
}