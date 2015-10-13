#ifndef __AE_SCENE_INDEXED_TRIANGLE_SET__
#define __AE_SCENE_INDEXED_TRIANGLE_SET__

namespace AE
{
	namespace Graphics
	{
		class IndexBuffer;
		class VertexBuffer;
	}

	namespace Scene
	{
		class IndexedTriangleSet : public X3DComposedGeometryNode
		{
		public:
			IndexedTriangleSet(AE::Graphics::VertexBuffer *vertexBuffer, AE::Graphics::IndexBuffer *indexBuffer)
				: mVertexBuffer(vertexBuffer), mIndexBuffer(indexBuffer) {}
			virtual ~X3DIndexedTriangleSet() { mIndexBuffer = 0; mVertexBuffer = 0; }

		private:
			AE::Graphics::IndexBuffer *mIndexBuffer;
			AE::Graphics::VertexBuffer *mVertexBuffer;
		};
	}
}

#endif