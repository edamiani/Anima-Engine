#ifndef __AE_GRAPHICS_SURFACE_FACTORY_DX11__
#define __AE_GRAPHICS_SURFACE_FACTORY_DX11__

#include "AnimaGraphicsSurfaceFactory.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		class SurfaceFactoryDX10 : public AE::Graphics::SurfaceFactory
		{
		public:
			SurfaceFactoryDX10();
			~SurfaceFactoryDX10();

			AE::Graphics::Surface* createSurface(const AE::Graphics::SurfaceDesc &surfaceDesc);
			void destroySurface(AE::Graphics::Surface *surface);
		};
	}
}

#endif