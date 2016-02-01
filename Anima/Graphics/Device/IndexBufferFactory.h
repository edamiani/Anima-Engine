#ifndef __AE_GRAPHICS_DEVICE_INDEX_BUFFER_FACTORY__
#define __AE_GRAPHICS_DEVICE_INDEX_BUFFER_FACTORY__

#include "Anima/Graphics/Device/IndexBuffer.h"

#include "Anima/Graphics/Enums.h"
#include "Anima/Graphics/SurfaceDesc.h"
#include "Anima/Math/Point2.h"
#include "Anima/Types.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class IndexBuffer;

			class IndexBufferFactory
			{
			public:
				IndexBufferFactory() { }
				virtual ~IndexBufferFactory() { }

				virtual AE::Graphics::Device::IndexBuffer* createIndexBuffer(AE::Graphics::Device::IndexBufferDesc const &indexBufferDesc) = 0;
				virtual void destroyIndexBuffer(AE::Graphics::Device::IndexBuffer *indexBuffer) = 0;

			protected:
			};
		}
	}
}

#endif