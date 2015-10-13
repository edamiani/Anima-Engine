#ifndef __AE_SCENE_X3D_LAYER__
#define __AE_SCENE_X3D_LAYER__

#include "AnimaSceneX3D_ChildNode.h"
#include "AnimaSceneX3D_LayerNode.h"
#include "AnimaSceneX3D_ViewpointNode.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class Layer : public _LayerNode
			{
			public:
				Layer() {}
				~Layer() {}

				void addChildren(_ChildNode* child) { mChildren.push_back(child); }
				void removeChildren(_ChildNode* child) { mChildren.remove(child); }

			protected:
				std::list<AE::Scene::X3D::_ChildNode *> mChildren;
				std::list<AE::Scene::X3D::_ViewpointNode *> mViewpoints;
			};
		}
	}
}

#endif