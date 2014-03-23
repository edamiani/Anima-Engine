#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_ALLEGRO_DX9__
#define __AE_GRAPHICS_DEVICE_CONTEXT_ALLEGRO_DX9__

#include "AnimaGraphicsDeviceContextAllegro.h"

#include <d3d9.h>

#include <vector>

namespace AE
{
	namespace Graphics
	{
		class DeviceContextAllegroDX9 : public AE::Graphics::DeviceContextAllegro
		{
		public:
			DeviceContextAllegroDX9(AE::Graphics::DeviceAllegro *graphicsDevice, AE::Graphics::DeviceContextOption deviceContextOptions);
			virtual ~DeviceContextAllegroDX9();

			IDirect3DDevice9* _getD3dDevice() { return mD3dDevice; }

		protected:
			IDirect3DDevice9	*mD3dDevice;
		};
	}
}

#endif