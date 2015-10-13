#ifndef __AE_GRAPHICS_DEVICE_DRIVER__
#define __AE_GRAPHICS_DEVICE_DRIVER__

#include "Anima/Graphics/AnimaGraphicsDeviceContextDesc.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Math/AnimaMathPoint2.h"

#include <list>
#include <string>
#include <vector>

namespace AE
{
	namespace OS
	{
		class Window;
	}

	namespace Graphics
	{
		namespace Device
		{
			class Context;
			class Pipeline;
			class PixelBuffer;

			class Driver
			{
			public:
				Driver(AE::uint deviceId, AE::Graphics::Device::DriverType driverType) 
					: mDeviceId(deviceId), mType(driverType), mRenderablePixelBufferId(0) {}
				~Driver() {}

				virtual AE::Graphics::Device::Context*	createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName = "") = 0;
				AE::Graphics::Device::Context*			getDeviceContext(AE::uint index) { return mDeviceContexts[index]; }
				AE::uint								getDeviceId() { return mDeviceId; }
				AE::Graphics::Device::DriverType		getType() { return mType; }

			protected:
				std::vector<AE::Graphics::Device::Context *> 
														mDeviceContexts;
				AE::uint								mDeviceId;
				AE::uint								mRenderablePixelBufferId;
				AE::Graphics::Device::DriverType		mType;
			};
		}
	}
}

#endif