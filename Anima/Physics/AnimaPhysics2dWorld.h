/*
-----------------------------------------------------------------------------

Class: World

Module: AE::Physics2d

Description: representation of a 2d physical world - all 2d bodies, shapes,
joints and materials should be inserted in a world to be actually calculated

-----------------------------------------------------------------------------
*/

#ifndef __AE_PHYSICS2D_WORLD__
#define __AE_PHYSICS2D_WORLD__

namespace AE
{
	namespace Physics2d
	{
		class World
		{
			World() { }
			virtual ~World() { }
		};
	}
}