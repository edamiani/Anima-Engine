#include "../include/AnimaGraphicsDrawingContextDX9.h"
#include "../include/AnimaGraphicsSurfaceDX9.h"

namespace AE
{
	namespace Graphics
	{
		DrawingContextDX9::DrawingContextDX9(AE::Graphics::DeviceContext *parentDeviceContext, IDirect3DSurface9 *surfaceDX9)
			: DrawingContext(parentDeviceContext)
		{
			mFrameBuffer = new AE::Graphics::SurfaceDX9(surfaceDX9);
		}

		DrawingContextDX9::~DrawingContextDX9()
		{
			delete mFrameBuffer;
		}
	}
}