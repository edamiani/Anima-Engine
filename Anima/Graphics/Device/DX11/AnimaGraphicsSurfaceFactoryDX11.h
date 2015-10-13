#ifndef __AE_GRAPHICS_SURFACE_FACTORY_DX11__
#define __AE_GRAPHICS_SURFACE_FACTORY_DX11__

#include "AnimaGraphicsSurfaceFactory.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		class SurfaceFactoryDX11 : public AE::Graphics::SurfaceFactory
		{
		public:
			SurfaceFactoryDX11();
			~SurfaceFactoryDX11();

			AE::Graphics::Surface* createSurface(const AE::Graphics::SurfaceDesc &surfaceDesc);
			void destroySurface(AE::Graphics::Surface *surface);
		};
	}
}

#endif