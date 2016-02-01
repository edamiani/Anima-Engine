#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE_RASTERIZER_GL15__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE_RASTERIZER_GL15__

#include "Anima/Graphics/Device/GL15/StageRasterizerGL15.h"

#include "Anima/Graphics/Device/SubpipelineRasterizer.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class SubpipelineRasterizerGL15 : public AE::Graphics::Device::SubpipelineRasterizer
			{
			public:
				SubpipelineRasterizerGL15(AE::Graphics::Device::SubpipelineType subpipelineType, AE::Graphics::Device::Pipeline *parentPipeline) : SubpipelineRasterizer(subpipelineType, parentPipeline) {}
				~SubpipelineRasterizerGL15() {}

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
				AE::Graphics::Device::StageRasterizerGL15	*mStageRasterizer;

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