#ifndef __AE_PHYSICS2D_BODY_BOX2D__
#define __AE_PHYSICS2D_BODY_BOX2D__

#include "AnimaPhysics2dBodyDesc.h"

class b2Body;

namespace AE
{
	namespace Physics2d
	{
		class BodyBox2d
		{
		public:
						BodyBox2d(const AE::Physics2d::BodyDesc &bodyDesc, AE::Physics2d::World *world);			
			virtual		~BodyBox2d();

			b2Body*		_getBox2dBody() { return mBody; }

		private:
			b2Body		*mBody;
		};
	}
}

#endif