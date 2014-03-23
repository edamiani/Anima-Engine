#ifndef __AE_SCENE_BINDABLE_NODE__
#define __AE_SCENE_BINDABLE_NODE__

#include "AnimaSceneChildNode.h"

namespace AE
{
	namespace Scene
	{
		class BindableNode : public AE::Scene::ChildNode
		{
		public:
			BindableNode(AE::Scene::Node *parentNode) : ChildNode(parentNode) {}
			virtual ~BindableNode() {}

			void setBind(bool enable) { mIsBound = enable; }
			bool isBound() { return mIsBound; }
			AE::Real getBindTime() { return mBindTime; }

		protected:
			AE::Real mBindTime;
			bool mIsBound;
		};
	}
}

#endif