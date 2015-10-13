#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE_2D_GL21__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE_2D_GL21__

#include "AnimaGraphicsDeviceSubpipeline2d.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageClipping2dGL21;
			class StageInput2dGL21;
			class StageTransformation2dGL21;

			class Subpipeline2dGL21 : public AE::Graphics::Device::Subpipeline2d
			{
			public:
				Subpipeline2dGL21(AE::Graphics::Device::SubpipelineType subpipelineType, AE::Graphics::Device::Pipeline *parentPipeline) : Subpipeline2d(subpipelineType, parentPipeline) {}
				~Subpipeline2dGL21() {}

				void									composeModelMatrix(AE::Math::Matrix4 const &modelMatrix);
				void									composeViewMatrix(AE::Math::Matrix4 const &viewMatrix);
				AE::Graphics::Device::Stage*			createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions = AE::NO_OPTIONS);
				AE::Graphics::Device::SubpipelinePtr	createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType);
				void									drawColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				void									drawTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix = true);
				void									enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				void									flush();
				AE::Math::Matrix4						getModelViewMatrix();
				void									popModelViewMatrix();
				void									pushModelViewMatrix();
				void									setModelMatrix(AE::Math::Matrix4 &modelMatrix);
				void									setViewMatrix(AE::Math::Matrix4 &viewMatrix);

				/***** Inherited from AE::Graphics::Device::Subpipeline

				AE::Graphics::Device::Stage*			addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage);
				AE::Graphics::Device::Stage*			addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage, AE::Graphics::Device::Stage *before);
				void									connectTo(AE::Graphics::Device::Subpipeline *subpipeline);
				void									disconnectFrom(AE::Graphics::Device::Subpipeline *subpipeline);
				AE::Graphics::Device::Pipeline*			getParentPipeline();
				void									removeStage(AE::Graphics::Device::Stage *stage);*/
				void									render();
				/*****/

			protected:
				AE::Graphics::Device::StageClipping2dGL21			*mStageClipping2d;
				AE::Graphics::Device::StageInput2dGL21				*mStageInput2d;
				AE::Graphics::Device::StageTransformation2dGL21	*mStageTransformation2d;

				/***** Inherited from AE::Graphics::Device::Subpipeline

				std::list<AE::Graphics::Device::SubpipelinePtr>		mAdjacencyList;
				AE::Graphics::Device::Pipeline						*mParentPipeline;
				std::map<AE::Graphics::Device::StageType, AE::Graphics::Device::Stage *>
																	mStages;
				AE::Graphics::Device::SubpipelineType				mType;
				*****/
			};
		}
	}
}

#endif