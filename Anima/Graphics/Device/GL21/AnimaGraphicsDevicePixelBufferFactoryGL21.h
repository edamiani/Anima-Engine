#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY_GL21__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY_GL21__

#include "AnimaGraphicsDevicePixelBufferFactory.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBufferFactoryGL21 : public AE::Graphics::Device::PixelBufferFactory
			{
			public:
				PixelBufferFactoryGL21();
				~PixelBufferFactoryGL21();

				AE::Graphics::Device::PixelBuffer* createPixelBuffer(AE::Graphics::Device::PixelBufferDesc const &pixelBufferDesc);
				void destroyPixelBuffer(AE::Graphics::Device::PixelBuffer *pixelBuffer);
			};
		}
	}
}

#endif