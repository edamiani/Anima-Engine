#include "../include/AnimaGraphicsDeviceContextAllegroDX9.h"

namespace AE
{
	namespace Graphics
	{
		DeviceContextAllegroDX9::DeviceContextAllegroDX9(AE::Graphics::DeviceAllegro *graphicsDevice, AE::Graphics::DeviceContextOption deviceContextOptions) 
			: mGraphicsDeviceAllegro(graphicsDevice, deviceContextOptions)
		{
			mD3dDevice = al_get_d3d_device(mAllegroDisplay);
		}

		DeviceContextAllegro::~DeviceContextAllegro()
		{
			mD3dDevice->Release();
			mD3dDevice = NULL;
		}
	}
}