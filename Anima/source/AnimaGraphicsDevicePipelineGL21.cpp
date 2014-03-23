#include "../include/AnimaGraphicsDevicePipelineGL21.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsDeviceSubpipeline2dGL21.h"
#include "../include/AnimaGraphicsDeviceSubpipeline3dGL21.h"
#include "../include/AnimaGraphicsDeviceSubpipelineRasterizerGL21.h"

#include "boost/shared_ptr.hpp"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			PipelineGL21::PipelineGL21(AE::Graphics::Device::Context *parentContext)
				: AE::Graphics::Device::Pipeline(parentContext)
			{
			}

			PipelineGL21::~PipelineGL21()
			{
				mSourceSubpipelines.clear();
			}

			AE::Graphics::Device::SubpipelinePtr PipelineGL21::createSourceSubpipeline(AE::Graphics::Device::SubpipelineType subPipelineType)
			{
				AE::Graphics::Device::SubpipelinePtr newSubpipeline;

				switch(subPipelineType)
				{
				case AE::Graphics::Device::SPLT_2D_OPERATIONS:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::Subpipeline2dGL21(subPipelineType, this));
					break;

				case AE::Graphics::Device::SPLT_3D_OPERATIONS:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::Subpipeline3dGL21(subPipelineType, this));
					break;

				case AE::Graphics::Device::SPLT_RASTERIZER:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::SubpipelineRasterizerGL21(subPipelineType, this));
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "PipelineGL21::createSourceSubpipeline(): this pipeline does not support this type of subpipeline.");
				}
				
				return mSourceSubpipelines[subPipelineType];
			}

			void PipelineGL21::enqueueTransformedColorBuffer(AE::Graphics::TransformedColorBuffer &transformedColorBuffer)
			{
				//mTransformedColorBuffers.push(transformedColorBuffer);
			}

			void PipelineGL21::render()
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