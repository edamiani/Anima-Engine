#include "../include/AnimaPhysics2dBodyStaticBox2d.h"

namespace AE
{
	namespace Physics2d
	{
		BodyStaticBox2d::BodyStaticBox2d(const AE::Physics2d::BodyDesc &bodyDesc)
			: BodyBox2d(bodyDesc)
		{
		}

		BodyStaticBox2d::~BodyStaticBox2d()
		{
		}
	}
}