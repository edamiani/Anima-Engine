#include "../include/AnimaGraphicsDeviceSubpipelineGL1_5.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceStageClipping2dGL1_5.h"
#include "../include/AnimaGraphicsDeviceStageInput2dGL1_5.h"
#include "../include/AnimaGraphicsDeviceStageRasterizerGL1_5.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			AE::Graphics::Device::Stage* SubpipelineGL1_5::createAndInsertStage(const std::string &stageName, AE::Graphics::Device::StageType stageType)
			{
				AE::Graphics::Device::Stage *newStage;

				switch(stageType)
				{
				case AE::Graphics::Device::ST_CLIPPING_2D:
					newStage = new AE::Graphics::Device::StageClipping2dGL1_5(this);
					break;

				case AE::Graphics::Device::ST_INPUT_2D:
					newStage = new AE::Graphics::Device::StageInput2dGL1_5(this);
					break;

				case AE::Graphics::Device::ST_RASTERIZER:
					newStage = new AE::Graphics::Device::StageRasterizerGL1_5(this);
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline::createAndInsertStage(): this pipeline does not support this type of stage.");
				}

				mStages.push_back(NamedStage(stageName, newStage));

				return newStage;
			}

			AE::Graphics::Device::SubpipelinePtr SubpipelineGL1_5::createSuccessor(const std::string &subpipelineName)
			{
				AE::Graphics::Device::SubpipelinePtr newSubpipeline(new AE::Graphics::Device::SubpipelineGL1_5(mParentPipeline));
				this->connectTo(newSubpipeline);

				mAdjacencyList.push_back(newSubpipeline);
				
				return newSubpipeline;
			}
		}
	}
}