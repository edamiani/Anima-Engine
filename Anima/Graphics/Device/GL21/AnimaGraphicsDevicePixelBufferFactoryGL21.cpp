#include "../include/AnimaGraphicsDevicePixelBufferFactoryGL21.h"

#include "../include/AnimaGraphicsDevicePixelBufferGL21.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			PixelBufferFactoryGL21::PixelBufferFactoryGL21()
			{
			}
			
			PixelBufferFactoryGL21::~PixelBufferFactoryGL21()
			{
			}

			AE::Graphics::Device::PixelBuffer* PixelBufferFactoryGL21::createPixelBuffer(AE::Graphics::Device::PixelBufferDesc const &pixelBufferDesc)
			{
				AE::Graphics::Device::PixelBuffer *pixelBuffer = new AE::Graphics::Device::PixelBufferGL21(pixelBufferDesc);

				return pixelBuffer;
			}

			void PixelBufferFactoryGL21::destroyPixelBuffer(AE::Graphics::Device::PixelBuffer *pixelBuffer)
			{
				delete pixelBuffer;
			}
		}
	}
}