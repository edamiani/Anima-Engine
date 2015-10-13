#ifndef __ANIMA_OS_RENDERING_CONTEXT_OSX__
#define __ANIMA_OS_RENDERING_CONTEXT_OSX__

#include "AnimaOSRenderingContext.h"

namespace AE
{
	namespace OS
	{
		class RenderingContextOSX : public RenderingContext
		{
		public:
			RenderingContextOSX(AE::Graphics::Surface *surface) : RenderingContext(surface) { }
			~RenderingContextOSX() { }

		protected:
			AE::Graphics::Surface *mSurface;
		};
	}
}

#endif