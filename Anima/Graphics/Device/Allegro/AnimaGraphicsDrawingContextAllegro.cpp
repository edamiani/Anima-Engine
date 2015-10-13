#include "../include/AnimaGraphicsDrawingContextAllegro.h"

namespace AE
{
	namespace Graphics
	{
		DrawingContextDX9::DrawingContextDX9(AE::Graphics::DeviceContext *parentDeviceContext, ALLEGRO_DISPLAY *allegroDisplay)
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