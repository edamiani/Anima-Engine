#ifndef __ANIMA_SCENE_FACTORY_X3D__
#define __ANIMA_SCENE_FACTORY_X3D__

#include "AnimaSceneFactory.h"

namespace AE
{
	namespace Graphics
	{
		class Manager;
		class Mesh;
	}

	namespace Scene
	{
		class FactoryX3D : public AE::Scene::Factory
		{
		public:
			FactoryX3D(AE::Graphics::Manager *graphicsManager) : mGraphicsManager(graphicsManager) { }
			~FactoryX3D() { mGraphicsManager = 0; }

			AE::Graphics::Indices* bakeRendererIndices(AE::Scene::MeshType meshType, AE::Graphics::Indices *indices);
			AE::Scene::ShapeNode* createShapeNode(AE::Graphics::Mesh *mesh, AE::Scene::GroupingNode *parentNode = 0);
			//Mesh* createMesh(AE::Graphics::RenderOperationType renderOperationType, AE::Graphics::VertexBuffer *vertexBuffer, AE::Graphics::IndexBuffer *indexBuffer = 0);

			AE::Graphics::Indices* _bakeRendererIndicesFromIndexedLineSet(AE::Graphics::Indices *indices);
			AE::Graphics::Indices* _bakeRendererIndicesFromIndexedTriangleFanSet(AE::Graphics::Indices *indices);
			AE::Graphics::Indices* _bakeRendererIndicesFromIndexedTriangleSet(AE::Graphics::Indices *indices);
			AE::Graphics::Indices* _bakeRendererIndicesFromIndexedTriangleStripSet(AE::Graphics::Indices *indices);

		private:
			AE::Graphics::Manager *mGraphicsManager;
		};
	}
}

#endif