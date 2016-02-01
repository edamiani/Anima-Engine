#ifndef __ANIMA_GRAPHICS_MESH__
#define __ANIMA_GRAPHICS_MESH__

#include <vector>

#include "Anima/Graphics/Geometry.h"
#include "Anima/Graphics/Device/IndexBuffer.h"
#include "Anima/Graphics/Device/VertexBuffer.h"
#include "Anima/Math/Vector3.h"

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

			AE::Graphics::Device::IndexBuffer*	getIndexBuffer(AE::uint index = 0) { return mIndexBuffer; }
			AE::Graphics::RenderOperationType	getRenderOperationType() { return mRenderOperationType; }
			AE::Graphics::Device::VertexBuffer*	getVertexBuffer(AE::uint index = 0) { return mVertexBuffer; }

		protected:
			AE::Graphics::Device::IndexBuffer	*mIndexBuffer;
			AE::Graphics::RenderOperationType	mRenderOperationType;
			AE::Graphics::Device::VertexBuffer	*mVertexBuffer;
		};
	}
}

#endif