#ifndef __AE_GRAPHICS_DRAWING_CONTEXT_DX9__
#define __AE_GRAPHICS_DRAWING_CONTEXT_DX9__

#include "AnimaGraphicsDrawingContext.h"

#include <d3d9.h>

namespace AE
{
	namespace Graphics
	{
		class DrawingContextDX9 : public AE::Graphics::DrawingContext
		{
		public:
			DrawingContextDX9(AE::Graphics::DeviceContext *parentDeviceContext, IDirect3DSurface9 *surfaceDX9);
			virtual ~DrawingContextDX9();

		protected:
		};
	}
}

#endif