#ifndef __AE_SCENE_X3D__VIEWPORT_NODE__
#define __AE_SCENE_X3D__VIEWPORT_NODE__

#include "AnimaSceneX3D_BoundedObject.h"
#include "AnimaSceneX3D_GroupingNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _ViewportNode : public AE::Scene::X3D::_GroupingNode
			{
			public:
				_ViewportNode() {}
				virtual ~_ViewportNode() {}
			};
		}
	}
}

#endif