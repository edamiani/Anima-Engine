#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE_2D_GL15__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE_2D_GL15__

#include "Anima/Graphics/Device/AnimaGraphicsDeviceSubpipeline2d.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageClipping2dGL15;
			class StageInput2dGL15;
			class StageTransformation2dGL15;

			class Subpipeline2dGL15 : public AE::Graphics::Device::Subpipeline2d
			{
			public:
				Subpipeline2dGL15(AE::Graphics::Device::SubpipelineType subpipelineType, AE::Graphics::Device::Pipeline *parentPipeline) : Subpipeline2d(subpipelineType, parentPipeline) {}
				~Subpipeline2dGL15() {}

				void									composeModelMatrix(AE::Math::Matrix4 const &modelMatrix);
				void									composeViewMatrix(AE::Math::Matrix4 const &viewMatrix);
				AE::Graphics::Device::Stage*			createAndInsertStage(AE::Graphics::Device::StageType stageType, AE::uint stageOptions = AE::NO_OPTIONS);
				AE::Graphics::Device::SubpipelinePtr	createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType);
				void									drawColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				void									drawTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix = true);
				void									enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer);
				//void									enqueueIndexBuffer(AE::Graphics::IndexBuffer *indexBuffer);
				//void									enqueueVertexBuffer(AE::Graphics::VertexBuffer *vertexBuffer);
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
				AE::Graphics::Device::StageClipping2dGL15			*mStageClipping2d;
				AE::Graphics::Device::StageInput2dGL15				*mStageInput2d;
				AE::Graphics::Device::StageTransformation2dGL15		*mStageTransformation2d;

				/*std::queue<AE::Graphics::Device::IndexBuffer *>		mIndexBuffers;
				std::queue<AE::Graphics::Device::VertexBuffer *>	mVertexBuffers;*/

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