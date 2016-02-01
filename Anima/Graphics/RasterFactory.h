#ifndef __AE_GRAPHICS_RASTER_FACTORY__
#define __AE_GRAPHICS_RASTER_FACTORY__

#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"

#include <cassert>

namespace AE
{
	namespace Graphics
	{
		struct Color;
		class Manager;
		class Surface;

		class RasterFactory
		{
		public:
			~RasterFactory() { }

			static AE::Graphics::RasterFactory*	getInstance() { assert(mInstance); return mInstance; }
			static AE::Graphics::RasterFactory*	initialize();
			static void shutdown();

			void drawLine(AE::Graphics::Surface *drawingSurface, const AE::Math::Point2<AE::int32> &start, const AE::Math::Point2<AE::int32> &end, const AE::Graphics::Color &color, AE::Graphics::LockType lockType = AE::Graphics::LT_NO_DIRTY_UPDATE);
		
		protected:
			RasterFactory();

			AE::int32 _round(AE::Real number);

			static AE::Graphics::RasterFactory *mInstance;
		};
	}
}

#endif