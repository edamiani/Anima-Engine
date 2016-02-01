#include "Anima/Graphics/Device/GL15/PixelBufferFactoryGL15.h"

#include "Anima/Graphics/Device/GL15/PixelBufferGL15.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			PixelBufferFactoryGL15::PixelBufferFactoryGL15()
			{
			}
			
			PixelBufferFactoryGL15::~PixelBufferFactoryGL15()
			{
			}

			AE::Graphics::Device::PixelBuffer* PixelBufferFactoryGL15::createPixelBuffer(AE::Graphics::Device::PixelBufferDesc const &pixelBufferDesc)
			{
				AE::Graphics::Device::PixelBuffer *pixelBuffer = new AE::Graphics::Device::PixelBufferGL15(pixelBufferDesc);

				return pixelBuffer;
			}

			void PixelBufferFactoryGL15::destroyPixelBuffer(AE::Graphics::Device::PixelBuffer *pixelBuffer)
			{
				delete pixelBuffer;
			}
		}
	}
}