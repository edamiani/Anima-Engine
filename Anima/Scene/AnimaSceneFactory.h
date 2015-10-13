#ifndef __AE_SCENE_FACTORY__
#define __AE_SCENE_FACTORY__

#include "AnimaGraphicsMesh.h"
#include "AnimaGraphicsTypedefs.h"
#include "AnimaSceneShapeNode.h"
#include "AnimaSceneEnums.h"

namespace AE
{
	namespace Graphics
	{
		class IndexBuffer;
		class Mesh;
		class VertexBuffer;
	}

	namespace Scene
	{
		class Factory
		{
		public:
			Factory() {}
			virtual ~Factory() {}

			virtual AE::Graphics::Indices* bakeRendererIndices(AE::Scene::MeshType meshType, AE::Graphics::Indices *indices) = 0;
			virtual AE::Scene::ShapeNode* createDrawableNode(AE::Graphics::Mesh *mesh, AE::Scene::GroupingNode *parentNode = 0) = 0;
			//virtual Mesh* createMesh(const MeshDesc &meshDesc) = 0;
		};
	}
}

#endif