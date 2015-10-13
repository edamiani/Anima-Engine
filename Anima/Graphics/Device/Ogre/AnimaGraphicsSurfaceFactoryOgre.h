#ifndef __AE_GRAPHICS_SURFACE_FACTORY_OGRE__
#define __AE_GRAPHICS_SURFACE_FACTORY_OGRE__

#include "AnimaGraphicsSurfaceFactory.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		class SurfaceFactoryOgre : public AE::Graphics::SurfaceFactory
		{
		public:
			SurfaceFactoryOgre();
			~SurfaceFactoryOgre();

			AE::Graphics::Surface* createSurface(const AE::Math::Point2 &dimensions, AE::Graphics::AllocationType allocationType);
			void destroySurface(AE::Graphics::Surface *surface);
		};
	}
}

#endif