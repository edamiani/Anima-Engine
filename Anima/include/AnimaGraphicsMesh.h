#ifndef __ANIMA_GRAPHICS_MESH__
#define __ANIMA_GRAPHICS_MESH__

#include <vector>

#include "AnimaGraphicsGeometry.h"
#include "AnimaGraphicsIndexBuffer.h"
#include "AnimaGraphicsVertexBuffer.h"
#include "AnimaMathVector3.h"

namespace AE
{
	namespace Graphics
	{
		class Mesh
		{
		public:
			Mesh(AE::Graphics::RenderOperationType renderOperationType,
				 AE::Graphics::VertexBuffer *vertexBuffer,
				 AE::Graphics::IndexBuffer *indexBuffer = 0) 
				: mRenderOperationType(renderOperationType),
				  mVertexBuffer(vertexBuffer), mIndexBuffer(indexBuffer) { }
			virtual ~Mesh() { }

			AE::Graphics::IndexBuffer* getIndexBuffer(AE::uint index = 0) { return mIndexBuffer; }
			AE::Graphics::RenderOperationType getRenderOperationType() { return mRenderOperationType; }
			AE::Graphics::VertexBuffer* getVertexBuffer(AE::uint index = 0) { return mVertexBuffer; }

		protected:
			AE::Graphics::IndexBuffer *mIndexBuffer;
			AE::Graphics::RenderOperationType mRenderOperationType;
			AE::Graphics::VertexBuffer *mVertexBuffer;
		};
	}
}


#endif