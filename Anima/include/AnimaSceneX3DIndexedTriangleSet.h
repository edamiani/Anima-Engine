#ifndef __AE_SCENE_X3D_INDEXED_TRIANGLE_SET__
#define __AE_SCENE_X3D_INDEXED_TRIANGLE_SET__

#include "AnimaSceneIndexedTriangleSet.h"
#include "AnimaSceneX3D_ComposedGeometryNode.h"

namespace AE
{
	namespace Scene
	{
		namespace X3D
		{
			class IndexedTriangleSet : public AE::Scene::IndexedTriangleSet, public AE::Scene::X3D::_ComposedGeometryNode
			{
			public:
				IndexedTriangleSet(AE::Graphics::VertexBuffer *vertexBuffer, AE::Graphics::IndexBuffer *indexBuffer)
					: IndexedTriangleSet(vertexBuffer, indexBuffer) {}
				virtual ~IndexedTriangleSet() {  }

			protected:
			};
		}
	}
}

#endif