#ifndef __AE_SCENE_X3D__BINDABLE_NODE__
#define __AE_SCENE_X3D__BINDABLE_NODE__

#include "AnimaSceneX3D_ChildNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class _BindableNode : public AE::Scene::X3D::_ChildNode
			{
			public:
				_BindableNode() {}
				virtual ~_BindableNode() {}

				void setBind(bool enable) { mIsBound = enable; }
				bool isBound() { return mIsBound; }
				AE::Real getBindTime() { return mBindTime; }

			protected:
				AE::Real mBindTime;
				bool mIsBound;
			};
		}
	}
}

#endif