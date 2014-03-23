#ifndef __AE_SCENE_SHAPE_NODE__
#define __AE_SCENE_SHAPE_NODE__

#include "AnimaGraphicsMesh.h"
#include "AnimaSceneGroupingNode.h"
#include "AnimaMathMatrix4.h"
#include "AnimaMathVector3.h"

#include <list>

namespace AE
{
	namespace Scene
	{
		class ShapeNode : public AE::Scene::ChildNode
		{
		public:
			ShapeNode(AE::Graphics::Mesh *mesh, AE::Scene::GroupingNode *parentNode = 0) 
				: ChildNode(parentNode), mMesh(mesh) 
			{
				mType = (AE::Scene::NodeType)(mType | AE::Scene::NT_SHAPE);
				parentNode->addChildNode(this);
			}

			virtual ~ShapeNode() {}

			AE::Graphics::Mesh* getMesh() { return mMesh; }
			void traverse();

		protected:
			AE::Graphics::Mesh *mMesh;
		};
	}
}

#endif