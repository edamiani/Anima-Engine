#ifndef __AE_SCENE_X3D__LAYER_NODE__
#define __AE_SCENE_X3D__LAYER_NODE__

#include "AnimaSceneX3D_Node.h"
#include "AnimaSceneX3D_ViewportNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _LayerNode : public _Node
			{
			public:
				_LayerNode() : mIsPickable(true), mViewport(0) {}
				virtual ~_LayerNode() {}

				bool isPickable() { return mIsPickable; }

			protected:
				bool mIsPickable;
				_ViewportNode *mViewport;
			};
		}
	}
}

#endif