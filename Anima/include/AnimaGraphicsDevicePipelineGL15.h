#ifndef __AE_GRAPHICS_DEVICE_PIPELINE_GL15__
#define __AE_GRAPHICS_DEVICE_PIPELINE_GL15__

#include "AnimaGraphicsDevicePipeline.h"
#include "AnimaGraphicsTransformedColorBuffer.h"

#include <queue>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageClipping2dGL15;
			class StageInput2dGL15;
			class StageRasterizerGL15;
			class StageTransformation2dGL15;

			class PipelineGL15 : public AE::Graphics::Device::Pipeline
			{
			public:
				PipelineGL15(AE::Graphics::Device::Context *parentContext);
				~PipelineGL15();

				void enqueueTransformedColorBuffer(AE::Graphics::TransformedColorBuffer &transformedColorBuffer);
				
				/***** Inherited from AE::Graphics::Device::Pipeline *****/
				AE::Graphics::Device::SubpipelinePtr createSourceSubpipeline(AE::Graphics::Device::SubpipelineType subPipelineType);
				void render();

			protected:
				std::queue<AE::Graphics::ColorBuffer *> mColorBuffers;
				std::queue<AE::Graphics::TransformedColorBuffer> mTransformedColorBuffers;

				friend class StageClipping2dGL15;
				friend class StageInput2dGL15;
				friend class StageRasterizerGL15;
				friend class StageTransformation2dGL15;

				/***** Inherited from AE::Graphics::Device::Pipeline *****
				std::map<std::string, AE::Graphics::Device::SubpipelinePtr> mSourceSubpipelines;
				*****/
			};
		}
	}
}

#endif