#ifndef __ANIMA_GRAPHICS_MESH__
#define __ANIMA_GRAPHICS_MESH__

#include <vector>

#include "AnimaGraphicsGeometry.h"
#include "AnimaGraphicsDeviceIndexBuffer.h"
#include "AnimaGraphicsDeviceVertexBuffer.h"
#include "../Math/AnimaMathVector3.h"

namespace AE
{
	namespace Graphics
	{
		class Mesh
		{
		public:
			Mesh(AE::Graphics::RenderOperationType renderOperationType,
				 AE::Graphics::Device::VertexBuffer *vertexBuffer,
				 AE::Graphics::Device::IndexBuffer *indexBuffer = 0) 
				: mRenderOperationType(renderOperationType),
				  mVertexBuffer(vertexBuffer), mIndexBuffer(indexBuffer) { }
			virtual ~Mesh() { }

			AE::Graphics::Device::IndexBuffer* getIndexBuffer(AE::uint index = 0) { return mIndexBuffer; }
			AE::Graphics::RenderOperationType getRenderOperationType() { return mRenderOperationType; }
			AE::Graphics::Device::VertexBuffer* getVertexBuffer(AE::uint index = 0) { return mVertexBuffer; }

		protected:
			AE::Graphics::Device::IndexBuffer *mIndexBuffer;
			AE::Graphics::RenderOperationType mRenderOperationType;
			AE::Graphics::Device::VertexBuffer *mVertexBuffer;
		};
	}
}


#endif