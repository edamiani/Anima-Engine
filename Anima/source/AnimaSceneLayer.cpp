#include "../include/AnimaSceneLayer.h"

#include "../include/AnimaSceneNode.h"

namespace AE
{
	namespace Scene
	{
		void Layer::traverse() 
		{
			std::list<AE::Scene::ChildNode *>::iterator i;
			for(i = mChildrenNodes.begin(); i != mChildrenNodes.end(); i++)
				(*i)->traverse();
		}
	}
}