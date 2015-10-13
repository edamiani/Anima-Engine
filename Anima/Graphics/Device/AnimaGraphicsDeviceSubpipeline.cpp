#include "AnimaGraphicsDeviceSubpipeline.h"

#include "AnimaGraphicsDeviceStage.h"

#include "Anima/AnimaException.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			Subpipeline::~Subpipeline()
			{
				std::map<AE::Graphics::Device::StageType, AE::Graphics::Device::Stage *>::iterator i;
				for(i = mStages.begin(); i != mStages.end(); i++)
					delete (*i).second;

				mStages.clear();
			}

			AE::Graphics::Device::Stage* Subpipeline::addStage(AE::Graphics::Device::StageType stageType, AE::Graphics::Device::Stage *stage)
			{
				mStages[stageType] = stage;

				return stage;
			}

			void Subpipeline::connectTo(SubpipelinePtr subpipeline)
			{
				std::list<SubpipelinePtr>::iterator i;
				
				for(i = mAdjacencyList.begin(); i != mAdjacencyList.end(); i++)
				{
					if((*i) == subpipeline)
						throw AE::Exception(AE::ET_ALREADY_EXISTS, "Subpipeline::connectTo(): subpipelines are already connected.");
				}

				SubpipelinePtr newPointer(subpipeline);
				mAdjacencyList.push_back(newPointer);
			}

			void Subpipeline::disconnectFrom(SubpipelinePtr subpipeline)
			{
				std::list<SubpipelinePtr>::iterator i;
				
				for(i = mAdjacencyList.begin(); i != mAdjacencyList.end(); i++)
				{
					if((*i) == subpipeline)
						mAdjacencyList.erase(i);

					return;
				}

				throw AE::Exception(AE::ET_NOT_FOUND, "Subpipeline::disconnectFrom(): subpipelines aren't connected.");
			}

			AE::Graphics::Device::Subpipeline* Subpipeline::findAdjacentSubpipeline(AE::Graphics::Device::SubpipelineType subpipelineType)
			{
				std::list<AE::Graphics::Device::SubpipelinePtr>::iterator i;
				for(i = mAdjacencyList.begin(); i != mAdjacencyList.end(); i++)
				{
					if((*i).get()->getType() == subpipelineType)
						return (*i).get();
					else
					{
						AE::Graphics::Device::Subpipeline* subpipeline = (*i).get()->findAdjacentSubpipeline(subpipelineType);
						
						if(subpipeline != 0)
							return subpipeline;
					}

				}

				return 0;
			}

			void Subpipeline::removeStage(AE::Graphics::Device::Stage *stage)
			{
				std::map<AE::Graphics::Device::StageType, AE::Graphics::Device::Stage *>::iterator i;
				
				for(i = mStages.begin(); i != mStages.end(); i++)
				{
					if((*i).second == stage)
						mStages.erase(i);

					return;
				}

				throw AE::Exception(AE::ET_NOT_FOUND, "Subpipeline::removeStage(): stage doesn't exist in this subpipeline.");
			}
		}
	}
}