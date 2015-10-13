#include "../include/AnimaGraphicsDeviceStageInput2dGL1_5.h"

#include "../include/AnimaGraphicsDeviceGLHeaders.h"
#include "../include/AnimaGraphicsDevicePipelineGL1_5.h"
#include "../include/AnimaGraphicsDevicePixelBuffer.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			StageInput2dGL1_5::StageInput2dGL1_5(AE::Graphics::Device::Subpipeline *parentSubpipeline)
				: StageInput2d(parentSubpipeline)
			{
				mPipeline = static_cast<AE::Graphics::Device::PipelineGL1_5 *>((*mParentSubpipelines.begin())->getParentPipeline());
			}

			StageInput2dGL1_5::~StageInput2dGL1_5()
			{
			}

			void StageInput2dGL1_5::enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer)
			{
				mPipeline->mColorBuffers.push(colorBuffer);
			}

			void StageInput2dGL1_5::enqueueTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix)
			{
				mPipeline->mTransformedColorBuffers.push(AE::Graphics::TransformedColorBuffer(colorBuffer, modelMatrix, resetModelMatrix));
			}

			void StageInput2dGL1_5::run()
			{
				mNextStage->run();
			}
		}
	}
}