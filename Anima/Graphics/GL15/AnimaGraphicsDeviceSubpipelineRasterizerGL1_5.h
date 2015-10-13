#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE_RASTERIZER_GL1_5__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE_RASTERIZER_GL1_5__

#include "AnimaGraphicsDeviceSubpipelineRasterizer.h"

#include "AnimaGraphicsDeviceStageRasterizerGL1_5.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class SubpipelineRasterizerGL1_5 : public AE::Graphics::Device::SubpipelineRasterizer
			{
			public:
				SubpipelineRasterizerGL1_5(AE::Graphics::Device::SubpipelineType subpipelineType, AE::Graphics::Device::Pipeline *parentPipeline) : SubpipelineRasterizer(subpipelineType, parentPipeline) {}
				~SubpipelineRasterizerGL1_5() {}

				AE::Graphics::Device::Stage*			createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions = AE::NO_OPTIONS);
				AE::Graphics::Device::SubpipelinePtr	createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType);

				/***** Inherited from AE::Graphics::Device::Subpipeline

				AE::Graphics::Device::Stage*			addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage);
				AE::Graphics::Device::Stage*			addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage, AE::Graphics::Device::Stage *before);
				void									connectTo(AE::Graphics::Device::Subpipeline *subpipeline);
				void									disconnectFrom(AE::Graphics::Device::Subpipeline *subpipeline);
				AE::Graphics::Device::Pipeline*			getParentPipeline();
				void									removeStage(AE::Graphics::Device::Stage *stage);*/
				void									render();
				/*****/

			protected:
				AE::Graphics::Device::StageRasterizerGL1_5	*mStageRasterizer;

				/***** Inherited from AE::Graphics::Device::Subpipeline

				std::list<boost::shared_ptr<AE::Graphics::Device::Subpipeline> > 
														mAdjacencyList;
				AE::Graphics::Device::Pipeline			*mParentPipeline;
				std::list<NamedStage>					mStages;
				******/
			};
		}
	}
}

#endif