#include "AnimaGraphicsDeviceStageInput2dGL15.h"

#include "AnimaGraphicsDevicePipelineGL15.h"

#include "AnimaGraphicsDeviceGLHeaders.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePixelBuffer.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			StageInput2dGL15::StageInput2dGL15(AE::Graphics::Device::Subpipeline *parentSubpipeline)
				: StageInput2d(parentSubpipeline)
			{
				mPipeline = static_cast<AE::Graphics::Device::PipelineGL15 *>((*mParentSubpipelines.begin())->getParentPipeline());
			}

			StageInput2dGL15::~StageInput2dGL15()
			{
			}

			void StageInput2dGL15::enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer)
			{
				mPipeline->mColorBuffers.push(colorBuffer);
			}

			//void StageInput2dGL15::enqueueIndexBuffer(AE::Graphics::IndexBuffer *indexBuffer)
			//{
			//	//mPipeline->
			//}

			//void StageInput2dGL15::enqueueVertexBuffer(AE::Graphics::VertexBuffer *vertexBuffer)
			//{
			//}

			void StageInput2dGL15::enqueueTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix)
			{
				mPipeline->mTransformedColorBuffers.push(AE::Graphics::TransformedColorBuffer(colorBuffer, modelMatrix, resetModelMatrix));
			}

			void StageInput2dGL15::run()
			{
				mNextStage->run();
			}
		}
	}
}