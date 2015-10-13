#ifndef __AE_GRAPHICS_DEVICE_SUBPIPELINE_2D__
#define __AE_GRAPHICS_DEVICE_SUBPIPELINE_2D__

#include "AnimaGraphicsDeviceSubpipeline.h"

#include "Anima/Math/AnimaMathMatrix4.h"

#include <queue>

namespace AE
{
	namespace Graphics
	{
		class ColorBuffer;

		namespace Device
		{
			class Subpipeline2d : public AE::Graphics::Device::Subpipeline
			{
			public:
				Subpipeline2d(AE::Graphics::Device::SubpipelineType subpipelineType, AE::Graphics::Device::Pipeline *parentPipeline) : Subpipeline(subpipelineType, parentPipeline) {}
				virtual ~Subpipeline2d() {}

				virtual void composeModelMatrix(AE::Math::Matrix4 const &modelMatrix) = 0;
				virtual void composeViewMatrix(AE::Math::Matrix4 const &viewMatrix) = 0;
				virtual void drawColorBuffer(AE::Graphics::ColorBuffer *colorBuffer) = 0;
				virtual void drawTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix = true) = 0;
				virtual void enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer) = 0;
				virtual void enqueueIndexBuffer(AE::Graphics::IndexBuffer *indexBuffer) = 0;
				virtual void enqueueVertexBuffer(AE::Graphics::VertexBuffer *vertexBuffer) = 0;
				virtual void flush() = 0;
				virtual AE::Math::Matrix4 getModelViewMatrix() = 0;
				virtual void popModelViewMatrix() = 0;
				virtual void pushModelViewMatrix() = 0;
				virtual void setModelMatrix(AE::Math::Matrix4 &modelMatrix) = 0;
				virtual void setViewMatrix(AE::Math::Matrix4 &viewMatrix) = 0;

				/***** Inherited from AE::Graphics::Device::Subpipeline

				AE::Graphics::Device::Stage*					addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage);
				AE::Graphics::Device::Stage*					addStage(const std::string &stageName, AE::Graphics::Device::Stage *stage, AE::Graphics::Device::Stage *before);
				void											connectTo(SubpipelinePtr subpipeline);
				virtual AE::Graphics::Device::Stage*			createAndInsertStage(const std::string &stageName, AE::Graphics::Device::StageType stageType, AE::uint stageOptions = AE::NO_OPTIONS) = 0;
				virtual AE::Graphics::Device::Subpipeline*		createSuccessor(AE::Graphics::Device::SubpipelineType subpipelineType) = 0;
				void											disconnectFrom(SubpipelinePtr subpipeline);
				AE::Graphics::Device::Subpipeline*				findAdjacentSubpipeline(AE::Graphics::Device::SubpipelineType subpipelineType);
				AE::Graphics::Device::Pipeline*					getParentPipeline() { return mParentPipeline; }
				AE::Graphics::Device::SubpipelineType			getType() { return mType };
				void											removeStage(AE::Graphics::Device::Stage *stage);
				virtual void									render() = 0;
				*****/

			protected:
				std::queue<AE::Graphics::IndexBuffer *> mIndexBuffers;
				std::queue<AE::Graphics::VertexBuffer *> mVertexBuffers;

				/***** Inherited from AE::Graphics::Device::Subpipeline *****
				std::list<boost::shared_ptr<AE::Graphics::Device::Subpipeline> > 
																mAdjacencyList;
				AE::Graphics::Device::Pipeline					*mParentPipeline;
				std::list<NamedStage>							mStages;
				******/
			};
		}
	}
}

#endif