#ifndef __AE_GRAPHICS_DEVICE_TRANSFORMED_COLOR_BUFFER__
#define __AE_GRAPHICS_DEVICE_TRANSFORMED_COLOR_BUFFER__

#include "../Math/AnimaMathMatrix4.h"

namespace AE
{
	namespace Graphics
	{
		class ColorBuffer;

		const bool RESETS_MODEL_MATRIX = true;
		const bool COMPOSES_MODEL_MATRIX = false;

		class TransformedColorBuffer
		{
		public:
			TransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix = false)
				: mColorBuffer(colorBuffer), mModelMatrix(modelMatrix), mResetModelMatrix(resetModelMatrix) { }

			virtual ~TransformedColorBuffer() {}

			AE::Graphics::ColorBuffer*	getColorBuffer() { return mColorBuffer; }
			AE::Math::Matrix4&			getModelMatrix() { return mModelMatrix; }
			bool						shouldResetModelMatrix() { return mResetModelMatrix; }

		private:
			AE::Graphics::ColorBuffer	*mColorBuffer;
			AE::Math::Matrix4			mModelMatrix;
			bool						mResetModelMatrix;
		};
	}
}

#endif