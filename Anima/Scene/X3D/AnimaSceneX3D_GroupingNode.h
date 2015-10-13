#ifndef __AE_SCENE_X3D__GROUPING_NODE__
#define __AE_SCENE_X3D__GROUPING_NODE__

#include "AnimaSceneX3D_BoundedObject.h"
#include "AnimaSceneX3D_ChildNode.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _GroupingNode : public AE::Scene::X3D::_BoundedObject, public AE::Scene::X3D::_ChildNode
			{
			public:
				_GroupingNode() {}
				virtual ~_GroupingNode() {}

				void addChildren(_ChildNode* child) { mChildrenNodes.push_back(child); }
				void removeChildren(_ChildNode* child) { mChildrenNodes.remove(child); }

			protected:
				std::list<AE::Scene::X3D::_ChildNode *> mChildrenNodes;
			};
		}
	}
}

#endif