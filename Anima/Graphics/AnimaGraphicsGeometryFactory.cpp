#include "../include/AnimaGraphicsColor.h"
#include "../include/AnimaGraphicsGeometryFactory.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaGraphicsSurface.h"

#include <cmath>

AE::Graphics::GeometryFactory* AE::Graphics::GeometryFactory::mInstance = 0;

namespace AE
{
	namespace Graphics
	{
		GeometryFactory::GeometryFactory()
		{
		}

		AE::Graphics::GeometryFactory* GeometryFactory::initialize()
		{
			if(!mInstance)
#			ifdef AE_PLATFORM_ALLEGRO
				mInstance = new AE::Graphics::GeometryFactoryAllegro();
#			else
				return 0;
#			endif

			return mInstance;
		}

		void GeometryFactory::shutdown()
		{
			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}
	}
}
