#ifndef __AE_GRAPHICS_VIEWPORT__
#define __AE_GRAPHICS_VIEWPORT__

#include "Anima/Graphics/Color.h"
#include "Anima/Math/Vector2.h"
#include "Anima/Math/Matrix4.h"

namespace AE
{
	namespace Graphics
	{
		class Camera;

		class Viewport
		{
		public:
			Viewport(AE::Graphics::Camera *camera) 
				: mCamera(camera), mLowerLeft(-1, -1), mUpperRight(1, 1) { }
			virtual ~Viewport() { }

			AE::Graphics::Color& getBackgroundColor() { return mBackgroundColor; }
			AE::Graphics::Camera* getCamera() { return mCamera; }
			AE::Math::Matrix4 getProjectionMatrix();
			void setBackgroundColor(AE::Graphics::Color backgroundColor);
			void setDimensions(const AE::Math::Vector2 &lowerLeft, const AE::Math::Vector2 &upperRight);

		protected:
			AE::Graphics::Color mBackgroundColor;
			AE::Graphics::Camera *mCamera;
			AE::Math::Vector2 mLowerLeft, mUpperRight;
		};
	}
}

#endif