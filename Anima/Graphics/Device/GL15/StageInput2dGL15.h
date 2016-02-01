#ifndef __AE_GRAPHICS_DEVICE_STAGE_INPUT_2D_GL15__
#define __AE_GRAPHICS_DEVICE_STAGE_INPUT_2D_GL15__

#include "Anima/Graphics/Device/StageInput2d.h"

#include "Anima/Graphics/Device/GL15/PipelineGL15.h"

#include "Anima/Graphics/Device/IndexBuffer.h"
#include "Anima/Graphics/Device/VertexBuffer.h"

#include <list>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PixelBuffer;
			class TransformedPixelBuffer;

			class StageInput2dGL15 : public AE::Graphics::Device::StageInput2d
			{
			public:
				StageInput2dGL15(AE::Graphics::Device::Subpipeline *parentSubpipeline);
				~StageInput2dGL15();

				/***** Inherited from AE::Graphics::Device::StageInput2d *****/
				void drawColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				void enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				//void enqueueIndexBuffer(AE::Graphics::Device::IndexBuffer *indexBuffer);
				void enqueueTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix);
				//void enqueueVertexBuffer(AE::Graphics::Device::VertexBuffer *vertexBuffer);
				
				/***** Inherited from AE::Graphics::Device::Stage *****/
				void run();

			private:
				AE::Graphics::Device::PipelineGL15 *mPipeline;

				/***** Inherited from AE::Graphics::Device::Stage *****
				AE::Graphics::Device::Subpipeline *mParentSubpipeline;
				AE::Graphics::Device::StageType mType;*/
			};
		}
	}
}

#endif