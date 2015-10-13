#ifndef __AE_GRAPHICS_DEVICE_STAGE_TRANSFORMATION2D__
#define __AE_GRAPHICS_DEVICE_STAGE_TRANSFORMATION2D__

#include "AnimaGraphicsDeviceStage.h"

#include "Anima/Graphics/AnimaGraphicsImage.h"
#include "Anima/Math/AnimaMathMatrix4.h"
#include "Anima/Math/AnimaMathPoint2.h"

//#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Subpipeline;

			class StageTransformation2d : public AE::Graphics::Device::Stage
			{
			public:
				StageTransformation2d(AE::Graphics::Device::StageType stageType, AE::Graphics::Device::Subpipeline *parentSubpipeline)
					: mType(stageType), mParentSubpipeline(parentSubpipeline) {}

				virtual ~StageTransformation2d() {}

				virtual void run() = 0;

				virtual void composeModelMatrix(AE::Math::Matrix4 const &modelMatrix) = 0;
				virtual void composeViewMatrix(AE::Math::Matrix4 const &viewMatrix) = 0;
				virtual AE::Math::Matrix4 getModelViewMatrix() = 0;
				virtual void popModelViewMatrix() = 0;
				virtual void pushModelViewMatrix() = 0;
				virtual void rotate(AE::Graphics::Image, AE::Real angle) = 0;
				virtual void scale(AE::Graphics::Image, const AE::Math::Point2 &scale) = 0;
				virtual void setModelMatrix(AE::Math::Matrix4 const &modelMatrix) = 0;
				virtual void setViewMatrix(AE::Math::Matrix4 const &viewMatrix) = 0;

			protected:

			};
		}
	}
}

#endif