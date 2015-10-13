#ifndef __AE_GRAPHICS_SURFACE_FACTORY_GL1_5__
#define __AE_GRAPHICS_SURFACE_FACTORY_GL1_5__

#include "AnimaGraphicsSurfaceFactory.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		class SurfaceFactoryGL1_5 : public AE::Graphics::SurfaceFactory
		{
		public:
			SurfaceFactoryGL1_5();
			~SurfaceFactoryGL1_5();

			AE::Graphics::Surface* createSurface(const AE::Graphics::SurfaceDesc &surfaceDesc);
			void destroySurface(AE::Graphics::Surface *surface);
		};
	}
}

#endif