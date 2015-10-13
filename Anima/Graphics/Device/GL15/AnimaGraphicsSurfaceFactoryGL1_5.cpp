#include "../include/AnimaGraphicsSurfaceFactoryGL1_5.h"
#include "../include/AnimaGraphicsSurfaceGL1_5.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		SurfaceFactoryGL1_5::SurfaceFactoryGL1_5() 
		{
		}

		SurfaceFactoryGL1_5::~SurfaceFactoryGL1_5() 
		{
		}

		AE::Graphics::Surface* SurfaceFactoryGL1_5::createSurface(const AE::Graphics::SurfaceDesc &surfaceDesc)
		{
			AE::Graphics::Surface *newSurface = new AE::Graphics::SurfaceGL1_5(surfaceDesc);

			return newSurface;
		}
		
		void SurfaceFactoryGL1_5::destroySurface(AE::Graphics::Surface *surface)
		{
			delete surface;
		}
	}
}