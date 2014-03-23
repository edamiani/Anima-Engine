#ifndef __AE_GRAPHICS_DEVICE_VERTEX_BUFFER_FACTORY__
#define __AE_GRAPHICS_DEVICE_VERTEX_BUFFER_FACTORY__

#include "AnimaGraphicsDeviceVertexBuffer.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsSurfaceDesc.h"
#include "AnimaMathPoint2.h"
#include "AnimaTypes.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class VertexBuffer;

			class VertexBufferFactory
			{
			public:
				VertexBufferFactory() { }
				virtual ~VertexBufferFactory() { }

				virtual AE::Graphics::Device::VertexBuffer* createVetrexBuffer(AE::Graphics::Device::VertexBufferDesc const &vertexBufferDesc) = 0;
				virtual void destroyVertexBuffer(AE::Graphics::Device::VertexBuffer *vertexBuffer) = 0;

			protected:
			};
		}
	}
}

#endif