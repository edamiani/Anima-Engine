#include "AnimaGraphicsDeviceSubpipelineRasterizerGL15.h"

#include "AnimaGraphicsDeviceStageRasterizerGL15.h"

#include "Anima/AnimaException.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePipeline.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			AE::Graphics::Device::Stage* SubpipelineRasterizerGL15::createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions)
			{
				AE::Graphics::Device::Stage *newStage;

				switch(stageType)
				{
				case AE::Graphics::Device::ST_RASTERIZER:
					newStage = new AE::Graphics::Device::StageRasterizerGL15(this, mParentPipeline->getParentContext()->getFrameBuffer());
					mStageRasterizer = static_cast<AE::Graphics::Device::StageRasterizerGL15 *>(newStage);
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline::createAndInsertStage(): this pipeline does not support this type of stage.");
				}

				mStages[stageType] = newStage;

				return newStage;
			}

			AE::Graphics::Device::SubpipelinePtr SubpipelineRasterizerGL15::createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType)
			{
				throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline2dGL15::createSuccessor(): this subpipeline does not support successors.");
			}

			void SubpipelineRasterizerGL15::render()
			{
				/*AE::Graphics::Device::Stage *stage = mStages.begin()->second;
				stage->begin();*/
			}
		}
	}
}