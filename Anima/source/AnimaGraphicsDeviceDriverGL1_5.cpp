#include "../include/AnimaGraphicsDeviceDriverGL1_5.h"

#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaGraphicsDeviceContextDesc.h"
#include "../include/AnimaGraphicsDeviceContextGL1_5.h"
#include "../include/AnimaGraphicsDevicePipeline.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			DriverGL1_5::DriverGL1_5(AE::uint deviceId) 
				: Driver(deviceId, AE::Graphics::Device::DT_GL_15) 
			{
				AE::Graphics::AxesConvention2d::horizontalDirection = AE::Graphics::HD_LEFT_TO_RIGHT;
				AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_BOTTOM_TO_TOP;
			}

			DriverGL1_5::~DriverGL1_5() 
			{
			}

			AE::Graphics::Device::Context* DriverGL1_5::createDeviceContext(AE::Graphics::Device::ContextDesc &contextDesc, const std::string &contextName)
			{
				AE::Graphics::Device::Context *deviceContext = new AE::Graphics::Device::ContextGL1_5(contextDesc, this);

				if (contextDesc.parentWindow) 
					contextDesc.parentWindow->attachDeviceContext(deviceContext);

				mDeviceContexts.push_back(deviceContext);

				return deviceContext;
			}
		}
	}
}