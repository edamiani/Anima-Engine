#ifndef __AE_GRAPHICS_SURFACE_FACTORY__
#define __AE_GRAPHICS_SURFACE_FACTORY__

#include "Anima/Graphics/Enums.h"
#include "Anima/Graphics/SurfaceDesc.h"
#include "Anima/Math/Point2.h"
#include "Anima/Types.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		class SurfaceFactory
		{
		public:
			SurfaceFactory();
			virtual ~SurfaceFactory() {}

			virtual AE::Graphics::Surface* createSurface(const AE::Graphics::SurfaceDesc &surfaceDesc) = 0;
			virtual void destroySurface(AE::Graphics::Surface *surface) = 0;

		protected:
		};
	}
}

#endif