#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_DX9__
#define __AE_GRAPHICS_DEVICE_CONTEXT_DX9__

#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceWin32.h"
#include "AnimaGraphicsSurfaceDX9.h"
#include "AnimaGraphicsDrawingContextDesc.h"
#include "AnimaGraphicsDrawingContextDX9.h"

#include <d3d9.h>

#include <vector>

namespace AE
{
	namespace Graphics
	{
		class DeviceContextDX9 : public AE::Graphics::DeviceContext
		{
		public:
			DeviceContextDX9(AE::Graphics::DeviceWin32 *graphicsDevice);
			virtual ~DeviceContextDX9();

			bool beginRendering();
			AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
			AE::Graphics::Surface* createOffscreenSurface(AE::uint16 width, AE::uint16 height, AE::Graphics::SurfaceFormat surfaceFormat);
			void endRendering();

			IDirect3DDevice9* _getDevice() { return mD3dDevice; }

		protected:
			IDirect3DDevice9	*mD3dDevice;
			AE::Graphics::DeviceWin32 *mGraphicsDevice;
		};
	}
}

#endif