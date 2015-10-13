#include "AnimaGraphicsDeviceSubpipeline2dGL15.h"

#include "AnimaGraphicsDeviceStageClipping2dGL15.h"
#include "AnimaGraphicsDeviceStageInput2dGL15.h"
#include "AnimaGraphicsDeviceStageTransformation2dGL15.h"
#include "AnimaGraphicsDeviceSubpipelineRasterizerGL15.h"

#include "Anima/AnimaException.h"
#include "Anima/Graphics/AnimaGraphicsAxesConvention2d.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePipeline.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			AE::Graphics::Device::Stage* Subpipeline2dGL15::createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions)
			{
				AE::Graphics::Device::Stage *newStage;

				switch(stageType)
				{
				case AE::Graphics::Device::ST_CLIPPING_2D:
					newStage = new AE::Graphics::Device::StageClipping2dGL15(this);
					mStageClipping2d = static_cast<AE::Graphics::Device::StageClipping2dGL15 *>(newStage);
					break;

				case AE::Graphics::Device::ST_INPUT_2D:
					newStage = new AE::Graphics::Device::StageInput2dGL15(this);
					mStageInput2d = static_cast<AE::Graphics::Device::StageInput2dGL15 *>(newStage);
					break;

				case AE::Graphics::Device::ST_TRANSFORMATION_2D:
					newStage = new AE::Graphics::Device::StageTransformation2dGL15(this);
					mStageTransformation2d = static_cast<AE::Graphics::Device::StageTransformation2dGL15 *>(newStage);
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline::createAndInsertStage(): this pipeline does not support this type of stage.");
				}

				mStages[stageType] = newStage;

				return newStage;
			}

			void Subpipeline2dGL15::composeModelMatrix(AE::Math::Matrix4 const &modelMatrix)
			{
				if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
				{
					AE::Math::Matrix4 tempMatrix(modelMatrix);
					tempMatrix._m[13] = -tempMatrix._m[13];
					mStageTransformation2d->composeModelMatrix(tempMatrix);
				}
				else
					mStageTransformation2d->composeModelMatrix(modelMatrix);
			}

			void Subpipeline2dGL15::composeViewMatrix(AE::Math::Matrix4 const &viewMatrix)
			{
				mStageTransformation2d->composeViewMatrix(viewMatrix);
			}

			AE::Graphics::Device::SubpipelinePtr Subpipeline2dGL15::createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType)
			{
				AE::Graphics::Device::SubpipelinePtr newSubpipeline;

				switch(subpipelineType)
				{
				case AE::Graphics::Device::SPLT_RASTERIZER:
					newSubpipeline = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::SubpipelineRasterizerGL15(subpipelineType, mParentPipeline));
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline2dGL15::createSuccessor(): this subpipeline does not support this type of subpipeline as its successor.");
				}

				mAdjacencyList.push_back(newSubpipeline);

				return newSubpipeline;
			}

			void Subpipeline2dGL15::drawColorBuffer(AE::Graphics::ColorBuffer *colorBuffer)
			{
				mStageInput2d->enqueueColorBuffer(colorBuffer);
				mStageInput2d->run();
			}

			void Subpipeline2dGL15::drawTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix)
			{
				mStageInput2d->enqueueColorBuffer(colorBuffer);
				mStageInput2d->run();
			}

			void Subpipeline2dGL15::enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer)
			{
				mStageInput2d->enqueueColorBuffer(colorBuffer);
			}

			/*void enqueueIndexBuffer(AE::Graphics::IndexBuffer *indexBuffer)
			{
				mStageInput2d->enqueueIndexBuffer(indexBuffer);
			}

			void enqueueVertexBuffer(AE::Graphics::VertexBuffer *vertexBuffer)
			{
				mStageInput2d->enqueueVertexBuffer(vertexBuffer);
			}*/

			void Subpipeline2dGL15::flush()
			{
				mStageInput2d->run();
			}

			AE::Math::Matrix4 Subpipeline2dGL15::getModelViewMatrix()
			{
				return mStageTransformation2d->getModelViewMatrix();
			}

			void Subpipeline2dGL15::popModelViewMatrix()
			{
				mStageTransformation2d->popModelViewMatrix();
			}

			void Subpipeline2dGL15::pushModelViewMatrix()
			{
				mStageTransformation2d->pushModelViewMatrix();
			}

			void Subpipeline2dGL15::render()
			{
			}

			void Subpipeline2dGL15::setModelMatrix(AE::Math::Matrix4 &modelMatrix)
			{
				if(AE::Graphics::AxesConvention2d::verticalDirection == AE::Graphics::VD_TOP_TO_BOTTOM)
				{
					AE::Math::Matrix4 tempMatrix(modelMatrix);
					tempMatrix._m[13] = -tempMatrix._m[13];
					mStageTransformation2d->setModelMatrix(tempMatrix);
				}
				else
					mStageTransformation2d->setModelMatrix(modelMatrix);
			}

			void Subpipeline2dGL15::setViewMatrix(AE::Math::Matrix4 &viewMatrix)
			{
				mStageTransformation2d->setViewMatrix(viewMatrix);
			}
		}
	}
}