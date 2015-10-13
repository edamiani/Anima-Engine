#ifndef __ANIMA_OS_RENDERING_CONTEXT_WIN32__
#define __ANIMA_OS_RENDERING_CONTEXT_WIN32__

#include "AnimaOSRenderingContext.h"

namespace AE
{
	namespace OS
	{
		class RenderingContextWin32 : public RenderingContext
		{
		public:
			RenderingContextWin32(AE::Graphics::Surface *surface) : RenderingContext(surface) { }
			~RenderingContextWin32() { }

		protected:
			AE::Graphics::Surface *mSurface;
		};
	}
}

#endif