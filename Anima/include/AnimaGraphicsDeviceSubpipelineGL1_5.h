#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE_GL1_5__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE_GL1_5__

#include "AnimaGraphicsDeviceSubpipeline.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class SubpipelineGL1_5 : public AE::Graphics::Device::Subpipeline
			{
			public:
				SubpipelineGL1_5(AE::Graphics::Device::Pipeline *parentPipeline) : Subpipeline(parentPipeline) {}
				~SubpipelineGL1_5() {}

				AE::Graphics::Device::Stage*		createAndInsertStage(const std::string &stageName, AE::Graphics::Device::StageType stageType);
				AE::Graphics::Device::SubpipelinePtr createSuccessor(const std::string &subpipelineName);

				/***** Inherited from AE::Graphics::Device::Subpipeline *****
				AE::Graphics::Device::Stage*		addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage);
				AE::Graphics::Device::Stage*		addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage, AE::Graphics::Device::Stage *before);
				void								connectTo(AE::Graphics::Device::Subpipeline *subpipeline);
				void								disconnectFrom(AE::Graphics::Device::Subpipeline *subpipeline);
				AE::Graphics::Device::Pipeline*		getParentPipeline() { return mParentPipeline; }
				void								removeStage(AE::Graphics::Device::Stage *stage);
				******/

			protected:
				/***** Inherited from AE::Graphics::Device::Subpipeline *****
				std::list<boost::shared_ptr<AE::Graphics::Device::Subpipeline> > mAdjacencyList;
				AE::Graphics::Device::Pipeline *mParentPipeline;
				std::list<NamedStage> mStages;
				******/
			};
		}
	}
}

#endif