#include "../include/AnimaGraphicsDrawingContextGL.h"
#include "../include/AnimaGraphicsSurfaceGL.h"
#include "../include/AnimaOSWindowMetrics.h"

namespace AE
{
	namespace Graphics
	{
		DrawingContextGL::DrawingContextGL(AE::Graphics::DeviceContext *parentDeviceContext, AE::OS::WindowMetrics &windowMetrics, AE::Graphics::SurfaceFormat surfaceFormat)
			: DrawingContext(parentDeviceContext)
		{
			mFrameBuffer = new AE::Graphics::SurfaceGL(windowMetrics.width, windowMetrics.height, surfaceFormat);
			static_cast<AE::Graphics::SurfaceGL *>(mFrameBuffer)->_setOffScreen(false);
		}

		DrawingContextGL::~DrawingContextGL()
		{
			delete mFrameBuffer;
		}
	}
}