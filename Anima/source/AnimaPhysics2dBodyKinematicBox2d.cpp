#include "../include/AnimaPhysics2dBodyKinematicBox2d.h"

namespace AE
{
	namespace Physics2d
	{
		BodyKinematicBox2d::BodyKinematicBox2d(const AE::Physics2d::BodyDesc &bodyDesc)
			: BodyBox2d(bodyDesc)
		{
		}

		BodyKinematicBox2d::~BodyKinematicBox2d()
		{
		}
	}
}