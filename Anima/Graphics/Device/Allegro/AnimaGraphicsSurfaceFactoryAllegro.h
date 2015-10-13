#ifndef __AE_GRAPHICS_SURFACE_FACTORY_ALLEGRO__
#define __AE_GRAPHICS_SURFACE_FACTORY_ALLEGRO__

#include "AnimaGraphicsSurfaceFactory.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		class SurfaceFactoryAllegro : public AE::Graphics::SurfaceFactory
		{
		public:
			SurfaceFactoryAllegro();
			~SurfaceFactoryAllegro();

			AE::Graphics::Surface* createSurface(const AE::Math::Point2 &dimensions, AE::Graphics::AllocationType allocationType);
			void destroySurface(AE::Graphics::Surface *surface);
		};
	}
}

#endif