#ifndef __AE_GRAPHICS_DEVICE_PIPELINE_GL21__
#define __AE_GRAPHICS_DEVICE_PIPELINE_GL21__

#include "AnimaGraphicsDevicePipeline.h"
#include "AnimaGraphicsTransformedColorBuffer.h"

#include <queue>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageClipping2dGL21;
			class StageInput2dGL21;
			class StageRasterizerGL21;
			class StageTransformation2dGL21;

			class PipelineGL21 : public AE::Graphics::Device::Pipeline
			{
			public:
				PipelineGL21(AE::Graphics::Device::Context *parentContext);
				~PipelineGL21();

				void enqueueTransformedColorBuffer(AE::Graphics::TransformedColorBuffer &transformedColorBuffer);
				
				/***** Inherited from AE::Graphics::Device::Pipeline *****/
				AE::Graphics::Device::SubpipelinePtr createSourceSubpipeline(AE::Graphics::Device::SubpipelineType subPipelineType);
				void render();

			protected:
				std::queue<AE::Graphics::ColorBuffer *> mColorBuffers;
				std::queue<AE::Graphics::TransformedColorBuffer> mTransformedColorBuffers;

				friend class StageClipping2dGL21;
				friend class StageInput2dGL21;
				friend class StageRasterizerGL21;
				friend class StageTransformation2dGL21;

				/***** Inherited from AE::Graphics::Device::Pipeline *****
				std::map<std::string, AE::Graphics::Device::SubpipelinePtr> mSourceSubpipelines;
				*****/
			};
		}
	}
}

#endif