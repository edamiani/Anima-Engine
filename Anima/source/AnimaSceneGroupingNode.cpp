#include "../include/AnimaSceneGroupingNode.h"

namespace AE
{
	namespace Scene
	{
		void GroupingNode::traverse() 
		{
			/*std::list<AE::Scene::Node *>::iterator i;
			for(i = mChildrenNodes.begin(); i != mChildrenNodes.end(); i++)
			{
				if(nodeType & AE::Scene::NT_TRANSFORM)
				{
					AE::Math::Matrix4 localMatrix = static_cast<AE::Scene::TransformNode *>(currentNode)->getTransformationMatrix();
					localMatrix = localMatrix * mMatrixStack.top();
					mMatrixStack.push(localMatrix);
				}

				std::list<AE::Scene::Node *> children = static_cast<AE::Scene::GroupingNode *>(currentNode)->getChildren();
				std::list<AE::Scene::Node *>::iterator i = children.begin();
				for(i; i != children.end(); i++)
					traverse(*i);

				if(nodeType & AE::Scene::NT_TRANSFORM)
					mMatrixStack.pop();
			}*/

			/*else if(nodeType & AE::Scene::NT_DRAWABLE)
			{
				//mGraphicsManager->render(mMatrixStack.top(), static_cast<AE::Scene::DrawableNode *>(currentNode)->getMesh());
			}*/
		}
	}
}