#include "AnimaGraphicsDeviceSubpipeline3dGL15.h"

#include "AnimaGraphicsDeviceSubpipelineRasterizerGL15.h"

#include "Anima/AnimaException.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePipeline.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			AE::Graphics::Device::Stage* Subpipeline3dGL15::createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions)
			{
				/*AE::Graphics::Device::Stage *newStage;

				switch(stageType)
				{
				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline3dGL15::createAndInsertStage(): this pipeline does not support this type of stage.");
				}

				mStages[stageType] = newStage;

				return newStage;*/
				return 0;
			}

			AE::Graphics::Device::SubpipelinePtr Subpipeline3dGL15::createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType)
			{
				AE::Graphics::Device::SubpipelinePtr newSubpipeline;

				switch(subpipelineType)
				{
				case AE::Graphics::Device::SPLT_RASTERIZER:
					newSubpipeline = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::SubpipelineRasterizerGL15(subpipelineType, mParentPipeline));
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline3dGL15::createSuccessor(): this subpipeline does not support this type of subpipeline as its successor.");
				}

				mAdjacencyList.push_back(newSubpipeline);

				return newSubpipeline;
			}

			void Subpipeline3dGL15::render()
			{
				/*AE::Graphics::Device::Stage *stage = mStages.begin()->second;
				stage->run();*/
			}
		}
	}
}