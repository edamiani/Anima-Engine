#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY_GL15__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY_GL15__

#include "AnimaGraphicsDevicePixelBufferFactory.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBufferFactoryGL15 : public AE::Graphics::Device::PixelBufferFactory
			{
			public:
				PixelBufferFactoryGL15();
				~PixelBufferFactoryGL15();

				AE::Graphics::Device::PixelBuffer* createPixelBuffer(AE::Graphics::Device::PixelBufferDesc const &pixelBufferDesc);
				void destroyPixelBuffer(AE::Graphics::Device::PixelBuffer *pixelBuffer);
			};
		}
	}
}

#endif