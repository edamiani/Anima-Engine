#ifndef __AE_SCENE_GROUPING_NODE__
#define __AE_SCENE_GROUPING_NODE__

#include "AnimaSceneChildNode.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class GroupingNode : public AE::Scene::ChildNode
		{
		public:
			GroupingNode(AE::Scene::Node *parentNode = 0) 
				: ChildNode(parentNode) 
			{
				mType = (AE::Scene::NodeType)(mType | AE::Scene::NT_GROUP);
			}

			virtual ~GroupingNode() {}

			void addChildNode(AE::Scene::ChildNode* childNode) { mChildrenNodes.push_back(childNode); }
			std::list<AE::Scene::ChildNode *>& getChildrenNodes() { return mChildrenNodes; }
			void removeChildNode(AE::Scene::ChildNode* childNode) { mChildrenNodes.remove(childNode); }
			void traverse();

		protected:
			std::list<AE::Scene::ChildNode *> mChildrenNodes;
		};
	}
}

#endif