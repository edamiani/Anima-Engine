#include "../include/AnimaGraphicsDeviceStageInput2dGL21.h"

#include "../include/AnimaGraphicsDeviceGLHeaders.h"
#include "../include/AnimaGraphicsDevicePipelineGL21.h"
#include "../include/AnimaGraphicsDevicePixelBuffer.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			StageInput2dGL21::StageInput2dGL21(AE::Graphics::Device::Subpipeline *parentSubpipeline)
				: StageInput2d(parentSubpipeline)
			{
				mPipeline = static_cast<AE::Graphics::Device::PipelineGL21 *>((*mParentSubpipelines.begin())->getParentPipeline());
			}

			StageInput2dGL21::~StageInput2dGL21()
			{
			}

			void StageInput2dGL21::enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer)
			{
				mPipeline->mColorBuffers.push(colorBuffer);
			}

			void StageInput2dGL21::enqueueTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix)
			{
				mPipeline->mTransformedColorBuffers.push(AE::Graphics::TransformedColorBuffer(colorBuffer, modelMatrix, resetModelMatrix));
			}

			void StageInput2dGL21::run()
			{
				mNextStage->run();
			}
		}
	}
}