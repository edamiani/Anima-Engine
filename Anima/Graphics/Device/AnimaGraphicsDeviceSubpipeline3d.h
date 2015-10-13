#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE_3D__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE_3D__

#include "AnimaGraphicsDeviceSubpipeline.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Subpipeline3d : public AE::Graphics::Device::Subpipeline
			{
			public:
				Subpipeline3d(AE::Graphics::Device::SubpipelineType subpipelineType, AE::Graphics::Device::Pipeline *parentPipeline) : Subpipeline(subpipelineType, parentPipeline) {}
				~Subpipeline3d() {}

				/***** Inherited from AE::Graphics::Device::Subpipeline

				AE::Graphics::Device::Stage*					addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage);
				AE::Graphics::Device::Stage*					addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage, AE::Graphics::Device::Stage *before);
				void											connectTo(SubpipelinePtr subpipeline);
				virtual AE::Graphics::Device::Stage*			createAndInsertStage(const std::string &stageName, AE::Graphics::Device::StageType stageType, AE::uint stageOptions = AE::NO_OPTIONS) = 0;
				virtual AE::Graphics::Device::Subpipeline*		createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType) = 0;
				void											disconnectFrom(SubpipelinePtr subpipeline);
				AE::Graphics::Device::Subpipeline*				findAdjacentSubpipeline(AE::Graphics::Device::SubpipelineType subpipelineType);
				AE::Graphics::Device::Pipeline*					getParentPipeline() { return mParentPipeline; }
				AE::Graphics::Device::SubpipelineType			getType() { return mType };
				void											removeStage(AE::Graphics::Device::Stage *stage);
				virtual void									render() = 0;
				*****/

			protected:
				/***** Inherited from AE::Graphics::Device::Subpipeline *****
				std::list<boost::shared_ptr<AE::Graphics::Device::Subpipeline> > 
																mAdjacencyList;
				AE::Graphics::Device::Pipeline					*mParentPipeline;
				std::list<NamedStage>							mStages;
				******/
			};
		}
	}
}

#endif