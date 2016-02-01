#ifndef __AE_GRAPHICS_DEVICE_VERTEX_BUFFER_FACTORY__
#define __AE_GRAPHICS_DEVICE_VERTEX_BUFFER_FACTORY__

#include "Anima/Graphics/Device/VertexBuffer.h"

#include "Anima/Types.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Graphics/SurfaceDesc.h"
#include "Anima/Math/Point2.h"

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