#ifndef __AE_SCENE_X3D_LAYOUT_LAYER__
#define __AE_SCENE_X3D_LAYOUT_LAYER__

#include "AnimaSceneX3D_LayerNode.h"
#include "AnimaSceneX3D_LayoutNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class LayoutLayer : public _LayerNode
			{
			public:
				LayoutLayer() {}
				virtual ~LayoutLayer() {}

			protected:
				_LayoutNode *mLayout;
			};
		}
	}
}

#endif