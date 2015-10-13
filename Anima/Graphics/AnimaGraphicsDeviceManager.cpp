#include "../include/AnimaGraphicsDeviceManager.h"

AE::Graphics::Device::Manager* AE::Graphics::Device::Manager::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			Manager::Manager() : AE::Plugin(AE::PT_GRAPHICS_DEVICE_MANAGER)
			{
			}
			
			Manager::~Manager()
			{
			}
		}
	}
}