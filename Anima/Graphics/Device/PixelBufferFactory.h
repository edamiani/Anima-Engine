#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY__

#include "Anima/Graphics/Device/PixelBufferDesc.h"

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
			class PixelBuffer;

			class PixelBufferFactory
			{
			public:
				PixelBufferFactory() { }
				virtual ~PixelBufferFactory() { }

				virtual AE::Graphics::Device::PixelBuffer* createPixelBuffer(AE::Graphics::Device::PixelBufferDesc const &pixelBufferDesc) = 0;
				virtual void destroyPixelBuffer(AE::Graphics::Device::PixelBuffer *pixelBuffer) = 0;

			protected:
			};
		}
	}
}

#endif