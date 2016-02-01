#ifndef __ANIMA_GRAPHICS_IMAGE__
#define __ANIMA_GRAPHICS_IMAGE__

#include "Anima/Graphics/Enums.h"
#include "Anima/Math/Point2.h"
#include "Anima/Graphics/Image.h"

namespace AE
{
	namespace Graphics
	{
		class Surface;

		class ImageRaw : public AE::Graphics::Image
		{
		public:
			ImageRaw::Graphics::ImageType(AE::Graphics::Surface *imageSurface)
				: Image(AE::Graphics::IT_RAW, imageSurface) {}
			virtual ~ImageRaw() { }

			//virtual const AE::Math::Point2 getDimensions() { return mDimensions; }
			AE::Graphics::Surface* getSurface() { return mSurface; }
			//virtual void load(const std::string &fileName) = 0;
			//virtual void save(const std::string &fileName) = 0;

		protected:
		};
	}
}

#endif