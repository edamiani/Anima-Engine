#ifndef __AE_GRAPHICS_DEVICE_STAGE_INPUT_2D_GL21__
#define __AE_GRAPHICS_DEVICE_STAGE_INPUT_2D_GL21__

#include "AnimaGraphicsDeviceStageInput2d.h"

#include "AnimaGraphicsDevicePipelineGL21.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBuffer;
			class TransformedPixelBuffer;

			class StageInput2dGL21 : public AE::Graphics::Device::StageInput2d
			{
			public:
				StageInput2dGL21(AE::Graphics::Device::Subpipeline *parentSubpipeline);
				~StageInput2dGL21();

				/***** Inherited from AE::Graphics::Device::StageInput2d *****/
				void drawColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				void enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				void enqueueTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix);
				
				/***** Inherited from AE::Graphics::Device::Stage *****/
				void run();

			private:
				AE::Graphics::Device::PipelineGL21 *mPipeline;

				/***** Inherited from AE::Graphics::Device::Stage *****
				AE::Graphics::Device::Subpipeline *mParentSubpipeline;
				AE::Graphics::Device::StageType mType;*/
			};
		}
	}
}

#endif