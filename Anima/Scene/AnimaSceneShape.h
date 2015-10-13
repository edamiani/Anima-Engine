#ifndef __AE_SCENE_DRAWABLE_NODE__
#define __AE_SCENE_DRAWABLE_NODE__

#include "AnimaGraphicsGeometry.h"
#include "AnimaSceneNode.h"
#include "AnimaMathMatrix4.h"
#include "AnimaMathVector3.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class Shape
		{
		public:
			Shape() {}
			virtual ~Shape() {}

		protected:
			AE::Graphics::Geometry *mGeometry;
		};
	}
}

#endif