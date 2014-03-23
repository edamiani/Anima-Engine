#ifndef __AE_SCENE_CHILD_NODE__
#define __AE_SCENE_CHILD_NODE__

#include "AnimaSceneNode.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class ChildNode : public AE::Scene::Node
		{
		public:
			ChildNode(AE::Scene::Node *parentNode = 0) 
				: Node(parentNode) 
			{
				mType = (AE::Scene::NodeType)(mType | AE::Scene::NT_CHILD);
			}

			virtual ~ChildNode() {}

			void traverse();
		};
	}
}

#endif