#include "../include/AnimaPhysics2dManagerBox2d.h"

#include "../include/AnimaPhysics2dWorldBox2d.h"

namespace AE
{
	namespace Physics2d
	{
		ManagerBox2d::ManagerBox2d()
		{
		}

		ManagerBox2d::~ManagerBox2d()
		{
		}

		AE::Physics2d::World* ManagerBox2d::createWorld(const std::string &name, const AE::Math::Vector2 &gravity)
		{
			mWorlds[name] = new AE::Physics2d::WorldBox2d(gravity);
		}
	}
}