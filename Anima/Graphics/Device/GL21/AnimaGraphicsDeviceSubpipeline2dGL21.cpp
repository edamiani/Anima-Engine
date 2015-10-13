#include "../include/AnimaGraphicsDeviceSubpipeline2dGL21.h"

#include "../include/AnimaException.h"
#include "../include/AnimaGraphicsAxesConvention2d.h"
#include "../include/AnimaGraphicsDeviceContext.h"
#include "../include/AnimaGraphicsDevicePipeline.h"
#include "../include/AnimaGraphicsDeviceStageClipping2dGL21.h"
#include "../include/AnimaGraphicsDeviceStageInput2dGL21.h"
#include "../include/AnimaGraphicsDeviceStageTransformation2dGL21.h"
#include "../include/AnimaGraphicsDeviceSubpipelineRasterizerGL21.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			AE::Graphics::Device::Stage* Subpipeline2dGL21::createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions)
			{
				AE::Graphics::Device::Stage *newStage;

				switch(stageType)
				{
				case AE::Graphics::Device::ST_CLIPPING_2D:
					newStage = new AE::Graphics::Device::StageClipping2dGL21(this);
					mStageClipping2d = static_cast<AE::Graphics::Device::StageClipping2dGL21 *>(newStage);
					break;

				case AE::Graphics::Device::ST_INPUT_2D:
					newStage = new AE::Graphics::Device::StageInput2dGL21(this);
					mStageInput2d = static_cast<AE::Graphics::Device::StageInput2dGL21 *>(newStage);
					break;

				case AE::Graphics::Device::ST_TRANSFORMATION_2D:
					newStage = new AE::Graphics::Device::StageTransformation2dGL21(this);
					mStageTransformation2d = static_cast<AE::Graphics::Device::StageTransformation2dGL21 *>(newStage);
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline::createAndInsertStage(): this pipeline does not support this type of stage.");
				}

				mStages[stageType] = newStage;

				return newStage;
			}

			void Subpipeline2dGL21::composeModelMatrix(AE::Math::Matrix4 const &modelMatrix)
			{
				mStageTransformation2d->composeModelMatrix(modelMatrix);
			}

			void Subpipeline2dGL21::composeViewMatrix(AE::Math::Matrix4 const &viewMatrix)
			{
				mStageTransformation2d->composeViewMatrix(viewMatrix);
			}

			AE::Graphics::Device::SubpipelinePtr Subpipeline2dGL21::createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType)
			{
				AE::Graphics::Device::SubpipelinePtr newSubpipeline;

				switch(subpipelineType)
				{
				case AE::Graphics::Device::SPLT_RASTERIZER:
					newSubpipeline = AE::Graphics::Device::SubpipelinePtr(new AE::Graphics::Device::SubpipelineRasterizerGL21(subpipelineType, mParentPipeline));
					break;

				default:
					throw AE::Exception(AE::ET_NOT_SUPPORTED, "Subpipeline2dGL21::createSuccessor(): this subpipeline does not support this type of subpipeline as its successor.");
				}

				mAdjacencyList.push_back(newSubpipeline);

				return newSubpipeline;
			}

			void Subpipeline2dGL21::drawColorBuffer(AE::Graphics::ColorBuffer *colorBuffer)
			{
				mStageInput2d->enqueueColorBuffer(colorBuffer);
				mStageInput2d->run();
			}

			void Subpipeline2dGL21::drawTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix)
			{
				mStageInput2d->enqueueColorBuffer(colorBuffer);
				mStageInput2d->run();
			}

			void Subpipeline2dGL21::enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer)
			{
				mStageInput2d->enqueueColorBuffer(colorBuffer);
			}

			void Subpipeline2dGL21::flush()
			{
				mStageInput2d->run();
			}

			AE::Math::Matrix4 Subpipeline2dGL21::getModelViewMatrix()
			{
				return mStageTransformation2d->getModelViewMatrix();
			}

			void Subpipeline2dGL21::popModelViewMatrix()
			{
				mStageTransformation2d->popModelViewMatrix();
			}

			void Subpipeline2dGL21::pushModelViewMatrix()
			{
				mStageTransformation2d->pushModelViewMatrix();
			}

			void Subpipeline2dGL21::render()
			{
			}

			void Subpipeline2dGL21::setModelMatrix(AE::Math::Matrix4 &modelMatrix)
			{
				mStageTransformation2d->setModelMatrix(modelMatrix);
			}

			void Subpipeline2dGL21::setViewMatrix(AE::Math::Matrix4 &viewMatrix)
			{
				mStageTransformation2d->setViewMatrix(viewMatrix);
			}
		}
	}
}