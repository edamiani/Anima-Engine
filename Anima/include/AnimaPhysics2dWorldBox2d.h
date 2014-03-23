/*
-----------------------------------------------------------------------------

Class: WorldBox2d

Module: AE::Physics2d

Description: realization of a 2d physical world using Box2d

-----------------------------------------------------------------------------
*/

#ifndef __AE_PHYSICS2D_WORLD_BOX2D__
#define __AE_PHYSICS2D_WORLD_BOX2D__

#include "AnimaMathVector2.h"
#include "AnimaPhysics2dWorld.h"

namespace AE
{
	namespace Physics2d
	{
		class WorldBox2d : public AE::Physics2d::World
		{
		public:
			WorldBox2d(const AE::Math::Vector2 &gravity);
			~WorldBox2d();

			b2World* _getBox2dWorld() { return mWorld; }

		private:
			b2World *mWorld;
		};
	}
}