#ifndef __AE_SCENE_LAYER__
#define __AE_SCENE_LAYER__

#include "AnimaSceneChildNode.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class ViewpointNode;

		class Layer : public AE::Scene::Node
		{
		public:
			Layer() {}
			~Layer() {}

			void addChildNode(AE::Scene::ChildNode* childNode) { mChildrenNodes.push_back(childNode); }
			void addViewpoint(AE::Scene::ViewpointNode *viewpoint) { mViewpoints.push_back(viewpoint); }
			std::list<AE::Scene::ChildNode *>& getChildrenNodes() { return mChildrenNodes; }
			void removeChildNode(AE::Scene::ChildNode* childNode) { mChildrenNodes.remove(childNode); }
			void removeViewpoint(AE::Scene::ViewpointNode *viewpoint) { mViewpoints.remove(viewpoint); }
			void traverse();

		protected:
			std::list<AE::Scene::ChildNode *> mChildrenNodes;
			std::list<AE::Scene::ViewpointNode *> mViewpoints;
		};
	}
}

#endif