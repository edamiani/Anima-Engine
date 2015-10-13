#include "AnimaGraphicsDevicePipeline.h"

#include "AnimaGraphicsDeviceSubpipeline.h"

#include "Anima/AnimaException.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			Pipeline::~Pipeline()
			{
				mSourceSubpipelines.clear();
			}

			AE::Graphics::Device::Subpipeline* Pipeline::getSubpipeline(AE::Graphics::Device::SubpipelineType subpipelineType)
			{
				std::map<AE::Graphics::Device::SubpipelineType, AE::Graphics::Device::SubpipelinePtr>::iterator i = mSourceSubpipelines.find(subpipelineType);

				if(i != mSourceSubpipelines.end())
					return (*i).second.get();
				else
					throw AE::Exception(AE::ET_NOT_FOUND, "Pipeline::getSubpipeline(): can't find the specified subpipeline.");
			}
		}
	}
}