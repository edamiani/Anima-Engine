#ifndef __AE_GRAPHICS_DEVICE_DRIVER_GL15__
#define __AE_GRAPHICS_DEVICE_DRIVER_GL15__

#include "Anima/Graphics/Device/AnimaGraphicsDeviceDriver.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class DriverGL15 : public AE::Graphics::Device::Driver
			{
			public:
				DriverGL15(AE::uint deviceId);
				~DriverGL15();

				AE::Graphics::Device::Context*		createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName = "");
				AE::Graphics::Device::VertexBuffer*	createEmptyVertexBuffer();
				void								destroyVertexBuffer(AE::Graphics::Device::VertexBuffer *vertexBuffer);
			};
		}
	}
}

#endif
