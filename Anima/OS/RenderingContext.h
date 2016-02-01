#ifndef __ANIMA_OS_RENDERING_CONTEXT__
#define __ANIMA_OS_RENDERING_CONTEXT__

namespace AE
{
	namespace Graphics
	{
		class Surface;
	}

	namespace OS
	{
		class RenderingContext
		{
		public:
			RenderingContext(AE::Graphics::Surface *surface) : mSurface(surface) { }
			~RenderingContext() { }

		protected:
			AE::Graphics::Surface *mSurface;
		};
	}
}

#endif