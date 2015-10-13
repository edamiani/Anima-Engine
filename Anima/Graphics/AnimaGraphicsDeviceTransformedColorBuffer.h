#ifndef __AE_GRAPHICS_DEVICE_TRANSFORMED_COLOR_BUFFER__
#define __AE_GRAPHICS_DEVICE_TRANSFORMED_COLOR_BUFFER__

#include "Anima/Math/AnimaMathMatrix4.h"

namespace AE
{
	namespace Graphics
	{
		class ColorBuffer;

		class TransformedColorBuffer
		{
		public:
			TransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::MathMatrix4 const &modelMatrix)
				: mColorBuffer(colorBuffer), mModelMatrix(modelMatrix) { }

			virtual ~TransformedColorBuffer() {}

			AE::Graphics::ColorBuffer*	getColorBuffer;
			AE::Math::Matrix4			mModelMatrix;

		protected:
			AE::Graphics::ColorBuffer	*mColorBuffer;
			AE::Math::Matrix4			mModelMatrix;
		};
	}
}

#endif