#ifndef __AE_GRAPHICS_DEVICE_STAGE_TRANSFORMATION2D_GL15__
#define __AE_GRAPHICS_DEVICE_STAGE_TRANSFORMATION2D_GL15__

#include "AnimaGraphicsDeviceStageTransformation2dGL15.h"

#include "Anima/Graphics/Device/AnimaGraphicsDeviceStage.h"
#include "Anima/Math/AnimaMathMatrix4.h"
#include "Anima/Math/AnimaMathPoint2.h"
#include "Anima/Math/AnimaMathRectangle.h"

namespace AE
{
	namespace Graphics
	{
		class Image;

		namespace Device
		{
			class Subpipeline;

			class StageTransformation2dGL15 : public AE::Graphics::Device::Stage
			{
			public:
				StageTransformation2dGL15(AE::Graphics::Device::Subpipeline *parentSubpipeline);
				~StageTransformation2dGL15();

				/***** Inherited from AE::Graphics::Device::StageTransformation2d *****/
				void run();
				
				void composeModelMatrix(AE::Math::Matrix4 const &modelMatrix);
				void composeViewMatrix(AE::Math::Matrix4 const &viewMatrix);
				AE::Math::Matrix4 getModelViewMatrix();
				void popModelViewMatrix();
				void pushModelViewMatrix();
				void rotate(AE::Graphics::Image *image, AE::Real angle);
				void scale(AE::Graphics::Image *image, const AE::Math::Point2<AE::int32> &scale);
				void setViewport(const AE::Math::Rectangle &viewport);
				void setModelMatrix(AE::Math::Matrix4 const &modelMatrix);
				void setViewMatrix(AE::Math::Matrix4 const &viewMatrix);

			private:
				AE::Math::Matrix4 mModelMatrix;
				AE::Math::Matrix4 mViewMatrix;
			};
		}
	}
}

#endif