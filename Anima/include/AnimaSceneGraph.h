#ifndef __AE_SCENE_GRAPH__
#define __AE_SCENE_GRAPH__

#include <stack>

#include "AnimaMathMatrix4.h"
#include "AnimaSceneGroupingNode.h"
#include "AnimaSceneLayerSet.h"

namespace AE
{
	namespace Scene
	{
		class LayerSet;

		class Graph : public AE::Scene::Node, public AE::Scene::LayerSet
		{
		public:
			Graph();
			virtual ~Graph();

			void traverse();

		protected:
			std::stack<AE::Math::Matrix4> mMatrixStack;
		};
	}
}

#endif