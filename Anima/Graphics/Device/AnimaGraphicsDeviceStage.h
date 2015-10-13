#ifndef __AE_GRAPHICS_DEVICE_STAGE__
#define __AE_GRAPHICS_DEVICE_STAGE__

#include "AnimaGraphicsDeviceSubpipeline.h"

#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Graphics/AnimaGraphicsTransformedColorBuffer.h"

#include <list>
#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Subpipeline;

			class Stage
			{
			public:
				Stage() {}

				Stage(AE::Graphics::Device::StageType stageType, AE::Graphics::Device::Subpipeline *parentSubpipeline)
					: mNextStage(0), mType(stageType) 
				{
					mParentSubpipelines.push_back(parentSubpipeline);
				}

				Stage(AE::Graphics::Device::StageType stageType, std::list<AE::Graphics::Device::Subpipeline *> &parentSubpipelines)
					: mType(stageType), mParentSubpipelines(parentSubpipelines) {}

				virtual ~Stage() {}

				void setNextStage(AE::Graphics::Device::Stage *nextStage) { mNextStage = nextStage; }

				virtual void run() = 0;

			protected:
				std::list<AE::Graphics::Device::Subpipeline *>	mParentSubpipelines;
				AE::Graphics::Device::Stage						*mNextStage;
				AE::Graphics::Device::StageType					mType;
			};
		}
	}
}

#endif