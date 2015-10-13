#ifndef __ANIMA_GRAPHICS_DEVICE_PIXEL_BUFFER_DESC__
#define __ANIMA_GRAPHICS_DEVICE_PIXEL_BUFFER_DESC__

#include "Anima/Graphics/AnimaGraphicsColorBufferDesc.h"
#include "Anima/Graphics/AnimaGraphicsColor.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"

namespace AE
{
	namespace Graphics
	{
		class ColorBuffer;

		namespace Device
		{
			struct PixelBufferDesc
			{
				AE::Graphics::AllocationType		allocationType;
				AE::Graphics::ColorBufferDesc		colorBufferDesc;
				AE::Graphics::ColorFormat			colorFormatConversion;
				AE::Graphics::Color					colorKey;
				AE::Graphics::Device::BufferUsage	usage;
				bool								usesColorKey;

				PixelBufferDesc() :
					allocationType(AE::Graphics::AT_VIDEO_MEMORY),
					colorFormatConversion(AE::Graphics::CF_UNKNOWN),
					colorKey(0, 0, 0, 0),
					usage(AE::Graphics::Device::BU_STATIC_READ),
					usesColorKey(false) {}
			};
		}
	}
}

#endif