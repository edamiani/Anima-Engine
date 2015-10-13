#include "../include/AnimaGraphicsDevicePipelineGL1_5.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceSubpipeline2dGL1_5.h"
#include "../include/AnimaGraphicsDeviceSubpipeline3dGL1_5.h"
#include "../include/AnimaGraphicsDeviceSubpipelineRasterizerGL1_5.h"

#include "boost/shared_ptr.hpp"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			PipelineGL1_5::PipelineGL1_5(AE::Graphics::Device::Context *parentContext)
				: AE::Graphics::Device::Pipeline(parentContext)
			{
			}

			PipelineGL1_5::~PipelineGL1_5()
			{
				mSourceSubpipelines.clear();
			}

			AE::Graphics::Device::SubpipelinePtr PipelineGL1_5::createSourceSubpipeline(AE::Graphics::Device::SubpipelineType subPipelineType)
			{
				AE::Graphics::Device::SubpipelinePtr newSubpipeline;

				switch(subPipelineType)
				{
				case AE::Graphics::Device::SPLT_2D_OPERATIONS:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::Subpipeline2dGL1_5(subPipelineType, this));
					break;

				case AE::Graphics::Device::SPLT_3D_OPERATIONS:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::Subpipeline3dGL1_5(subPipelineType, this));
					break;

				case AE::Graphics::Device::SPLT_RASTERIZER:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::SubpipelineRasterizerGL1_5(subPipelineType, this));
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "PipelineGL1_5::createSourceSubpipeline(): this pipeline does not support this type of subpipeline.");
				}
				
				return mSourceSubpipelines[subPipelineType];
			}

			void PipelineGL1_5::enqueueTransformedColorBuffer(AE::Graphics::TransformedColorBuffer &transformedColorBuffer)
			{
				//mTransformedColorBuffers.push(transformedColorBuffer);
			}

			void PipelineGL1_5::render()
			{
				std::map<AE::Graphics::Device::SubpipelineType, AE::Graphics::Device::SubpipelinePtr>::iterator i;
				for(i = mSourceSubpipelines.begin(); i != mSourceSubpipelines.end(); i++)
				{
					AE::Graphics::Device::SubpipelinePtr p = i->second;
					p.get()->render();
				}
			}
		}
	}
}