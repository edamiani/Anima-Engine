/*
-------------------------------------------------------------------------------

Class: Object2d

Module: AE::Scene

Description: a complete 2d object, composed of a visual part and a physical 
part

-------------------------------------------------------------------------------
*/

#ifndef __AE_SCENE_OBJECT2D__
#define __AE_SCENE_OBJECT2D__

#include "AnimaGraphicsDrawable.h"
#include "AnimaPhysics2dBody.h"

namespace AE
{
	namespace Scene
	{
		class Object2d
		{
		public:
			Object2d();
			~Object2d();

			void update();

		private:
			AE::Graphics::Drawable	*mDrawable;
			AE::Physics2d::Body		*mBody;
		};
	}
}