#include "../include/AnimaSceneGraph.h"

namespace AE
{
	namespace Scene
	{
		Graph::Graph() 
		{
			mType = (AE::Scene::NodeType)(mType | AE::Scene::NT_ROOT);

			AE::Math::Matrix4 identity;
			identity.setIdentity();
			mMatrixStack.push(identity);
		}

		Graph::~Graph() 
		{
			while(!mMatrixStack.empty())
				mMatrixStack.pop();
		}

		void Graph::traverse()
		{
			std::list<AE::uint>::iterator i;
			for(i = mOrder.begin(); i != mOrder.end(); i++)
				mLayers[(*i)]->traverse();
		}
	}
}