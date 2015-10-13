#ifndef __AE_GRAPHICS_DRAWING_CONTEXT_GL__
#define __AE_GRAPHICS_DRAWING_CONTEXT_GL__

#include "AnimaGraphicsDrawingContext.h"

namespace AE
{
	namespace Graphics
	{
		class DrawingContextGL : public AE::Graphics::DrawingContext
		{
		public:
			DrawingContextGL(AE::Graphics::DeviceContext *parentDeviceContext, AE::OS::WindowMetrics &windowMetrics, AE::Graphics::SurfaceFormat surfaceFormat);
			virtual ~DrawingContextGL();

		protected:
		};
	}
}

#endif