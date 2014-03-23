#ifndef __ANIMA_OS_RENDERING_CONTEXT_LINUX__
#define __ANIMA_OS_RENDERING_CONTEXT_LINUX__

#include "AnimaOSRenderingContext.h"

namespace AE
{
	namespace OS
	{
		class RenderingContextLinux : public RenderingContext
		{
		public:
			RenderingContextLinux(AE::Graphics::Surface *surface) : RenderingContext(surface) { }
			~RenderingContextLinux() { }

		protected:
			AE::Graphics::Surface *mSurface;
		};
	}
}

#endif
