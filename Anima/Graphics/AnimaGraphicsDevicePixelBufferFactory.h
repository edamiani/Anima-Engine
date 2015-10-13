#ifndef __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY__
#define __AE_GRAPHICS_DEVICE_PIXEL_BUFFER_FACTORY__

#include "AnimaGraphicsDevicePixelBufferDesc.h"
#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsSurfaceDesc.h"
#include "../Math/AnimaMathPoint2.h"
#include "../AnimaTypes.h"

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