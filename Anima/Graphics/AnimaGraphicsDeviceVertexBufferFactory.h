#ifndef __AE_GRAPHICS_DEVICE_VERTEX_BUFFER_FACTORY__
#define __AE_GRAPHICS_DEVICE_VERTEX_BUFFER_FACTORY__

#include "AnimaGraphicsDeviceVertexBuffer.h"

#include "Anima/AnimaTypes.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Graphics/AnimaGraphicsSurfaceDesc.h"
#include "Anima/Math/AnimaMathPoint2.h"

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