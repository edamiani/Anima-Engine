#ifndef __AE_SCENE_X3D_LAYOUT_GROUP__
#define __AE_SCENE_X3D_LAYOUT_GROUP__

#include "AnimaSceneX3D_GroupingNode.h"
#include "AnimaSceneX3D_LayoutNode.h"
#include "AnimaSceneX3D_ViewportNode.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class LayoutGroup : public _GroupingNode
			{
			public:
				LayoutGroup() {}
				virtual ~LayoutGroup() {}

			protected:
				AE::Scene::X3D::_LayoutNode *mLayout;
				AE::Scene::X3D::_ViewportNode;
			};
		}
	}
}

#endif