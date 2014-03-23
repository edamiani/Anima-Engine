#ifndef __AE_SCENE_MOVABLE_NODE__
#define __AE_SCENE_MOVABLE_NODE__

#include "AnimaSceneNode.h"
#include "AnimaMathMatrix4.h"
#include "AnimaMathVector3.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class MovableNode : public AE::Scene::Node
		{
		public:
			MovableNode(AE::Scene::Node *parentNode = 0) 
				: Node(parentNode), mNodeType(AE::Scene::NT_DRAWABLE) {  }
			virtual ~MovableNode() {}

		protected:

		};
	}
}

#endif