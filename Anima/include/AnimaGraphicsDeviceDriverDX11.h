#ifndef __AE_GRAPHICS_DEVICE_DRIVER_DX11__
#define __AE_GRAPHICS_DEVICE_DRIVER_DX11__

#include "AnimaGraphicsDeviceDriver.h"

#include "d3d11.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class DriverDX11 : public AE::Graphics::Device::Driver
			{
			public:
				DriverDX11(AE::uint deviceId, IDXGIAdapter1 *device);
				~DriverDX11();

				AE::Graphics::Device::Context* createDeviceContext(AE::OS::Window *window, const std::string &contextName = "");

				ID3D11Device* _getD3d11Device() { return mD3d11Device; }
				ID3D11DeviceContext* _getD3d11DeviceContext() { return mD3d11DeviceContext; }
				D3D_FEATURE_LEVEL _getD3dFeatureLevel() { return mFeatureLevel; }

			protected:
				ID3D11Device* mD3d11Device;
				ID3D11DeviceContext *mD3d11DeviceContext;
				D3D_FEATURE_LEVEL mFeatureLevel;
			};
		}
	}
}

#endif