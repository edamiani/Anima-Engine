#include "../include/AnimaGraphicsDeviceSubpipelineRasterizerGL1_5.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceContext.h"
#include "../include/AnimaGraphicsDevicePipeline.h"
#include "../include/AnimaGraphicsDeviceStageRasterizerGL1_5.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			AE::Graphics::Device::Stage* SubpipelineRasterizerGL1_5::createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions)
			{
				AE::Graphics::Device::Stage *newStage;

				switch(stageType)
				{
				case AE::Graphics::Device::ST_RASTERIZER:
					newStage = new AE::Graphics::Device::StageRasterizerGL1_5(this, mParentPipeline->getParentContext()->getFrameBuffer());
					mStageRasterizer = static_cast<AE::Graphics::Device::StageRasterizerGL1_5 *>(newStage);
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline::createAndInsertStage(): this pipeline does not support this type of stage.");
				}

				mStages[stageType] = newStage;

				return newStage;
			}

			AE::Graphics::Device::SubpipelinePtr SubpipelineRasterizerGL1_5::createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType)
			{
				throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline2dGL1_5::createSuccessor(): this subpipeline does not support successors.");
			}

			void SubpipelineRasterizerGL1_5::render()
			{
				/*AE::Graphics::Device::Stage *stage = mStages.begin()->second;
				stage->begin();*/
			}
		}
	}
}