#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE__

#include "Anima/AnimaEnums.h"
#include "Anima/AnimaTypes.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"

#include <memory>

#include <list>
#include <map>
#include <string>
#include <utility>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Pipeline;
			class Subpipeline;
			class Stage;

			typedef std::pair<std::string, AE::Graphics::Device::Stage *> NamedStage;
			typedef std::shared_ptr<AE::Graphics::Device::Subpipeline> SubpipelinePtr;

			class Subpipeline
			{
			public:
				Subpipeline(AE::Graphics::Device::SubpipelineType subpipelineType, AE::Graphics::Device::Pipeline *parentPipeline) 
					: mParentPipeline(parentPipeline), mType(subpipelineType) {}
				virtual ~Subpipeline();

				AE::Graphics::Device::Stage*				addStage(AE::Graphics::Device::StageType stageType, AE::Graphics::Device::Stage *stage);
				void										connectTo(SubpipelinePtr subpipeline);
				virtual AE::Graphics::Device::Stage*		createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions = AE::NO_OPTIONS) = 0;
				virtual AE::Graphics::Device::SubpipelinePtr	createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType) = 0;
				void										disconnectFrom(SubpipelinePtr subpipeline);
				AE::Graphics::Device::Subpipeline*			findAdjacentSubpipeline(AE::Graphics::Device::SubpipelineType subpipelineType);
				AE::Graphics::Device::Pipeline*				getParentPipeline() { return mParentPipeline; }
				AE::Graphics::Device::SubpipelineType		getType() { return mType; }
				void										removeStage(AE::Graphics::Device::Stage *stage);
				virtual void								render() = 0;

			protected:
				std::list<AE::Graphics::Device::SubpipelinePtr> 
															mAdjacencyList;
				AE::Graphics::Device::Pipeline				*mParentPipeline;
				std::map<AE::Graphics::Device::StageType, AE::Graphics::Device::Stage *>
															mStages;
				AE::Graphics::Device::SubpipelineType		mType;
			};
		}
	}
}

#endif