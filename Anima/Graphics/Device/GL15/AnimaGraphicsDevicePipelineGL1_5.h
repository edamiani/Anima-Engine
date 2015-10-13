#ifndef __AE_GRAPHICS_DEVICE_PIPELINE_GL1_5__
#define __AE_GRAPHICS_DEVICE_PIPELINE_GL1_5__

#include "AnimaGraphicsDevicePipeline.h"
#include "AnimaGraphicsTransformedColorBuffer.h"

#include <queue>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageClipping2dGL1_5;
			class StageInput2dGL1_5;
			class StageRasterizerGL1_5;
			class StageTransformation2dGL1_5;

			class PipelineGL1_5 : public AE::Graphics::Device::Pipeline
			{
			public:
				PipelineGL1_5(AE::Graphics::Device::Context *parentContext);
				~PipelineGL1_5();

				void enqueueTransformedColorBuffer(AE::Graphics::TransformedColorBuffer &transformedColorBuffer);
				
				/***** Inherited from AE::Graphics::Device::Pipeline *****/
				AE::Graphics::Device::SubpipelinePtr createSourceSubpipeline(AE::Graphics::Device::SubpipelineType subPipelineType);
				void render();

			protected:
				std::queue<AE::Graphics::ColorBuffer *> mColorBuffers;
				std::queue<AE::Graphics::TransformedColorBuffer> mTransformedColorBuffers;

				friend class StageClipping2dGL1_5;
				friend class StageInput2dGL1_5;
				friend class StageRasterizerGL1_5;
				friend class StageTransformation2dGL1_5;

				/***** Inherited from AE::Graphics::Device::Pipeline *****
				std::map<std::string, AE::Graphics::Device::SubpipelinePtr> mSourceSubpipelines;
				*****/
			};
		}
	}
}

#endif