#include "Anima/Graphics/Device/GL15/PipelineGL15.h"

#include "Anima/Graphics/Device/GL15/Subpipeline2dGL15.h"
#include "Anima/Graphics/Device/GL15/Subpipeline3dGL15.h"
#include "Anima/Graphics/Device/GL15/SubpipelineRasterizerGL15.h"

#include "Anima/Exception.h"

#include "boost/shared_ptr.hpp"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			PipelineGL15::PipelineGL15(AE::Graphics::Device::Context *parentContext)
				: AE::Graphics::Device::Pipeline(parentContext)
			{
			}

			PipelineGL15::~PipelineGL15()
			{
				mSourceSubpipelines.clear();
			}

			AE::Graphics::Device::SubpipelinePtr PipelineGL15::createSourceSubpipeline(AE::Graphics::Device::SubpipelineType subPipelineType)
			{
				AE::Graphics::Device::SubpipelinePtr newSubpipeline;

				switch(subPipelineType)
				{
				case AE::Graphics::Device::SPLT_2D_OPERATIONS:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::Subpipeline2dGL15(subPipelineType, this));
					break;

				case AE::Graphics::Device::SPLT_3D_OPERATIONS:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::Subpipeline3dGL15(subPipelineType, this));
					break;

				case AE::Graphics::Device::SPLT_RASTERIZER:
					mSourceSubpipelines[subPipelineType] = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::SubpipelineRasterizerGL15(subPipelineType, this));
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "PipelineGL15::createSourceSubpipeline(): this pipeline does not support this type of subpipeline.");
				}
				
				return mSourceSubpipelines[subPipelineType];
			}

			void PipelineGL15::enqueueTransformedColorBuffer(AE::Graphics::TransformedColorBuffer &transformedColorBuffer)
			{
				//mTransformedColorBuffers.push(transformedColorBuffer);
			}

			void PipelineGL15::render()
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