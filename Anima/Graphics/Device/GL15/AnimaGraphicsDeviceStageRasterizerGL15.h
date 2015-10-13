#ifndef __AE_GRAPHICS_DEVICE_STAGE_RASTERIZER_GL15__
#define __AE_GRAPHICS_DEVICE_STAGE_RASTERIZER_GL15__

#include "AnimaGraphicsDevicePipelineGL15.h"

#include "Anima/Graphics/Device/AnimaGraphicsDeviceStageRasterizer.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageRasterizerGL15 : public AE::Graphics::Device::StageRasterizer
			{
			public:
				StageRasterizerGL15(AE::Graphics::Device::Subpipeline *parentSubpipeline, AE::Graphics::Device::FrameBuffer *frameBuffer);
				StageRasterizerGL15(std::list<AE::Graphics::Device::Subpipeline *> &parentSubpipelines, AE::Graphics::Device::FrameBuffer *frameBuffer);
				~StageRasterizerGL15();

				void enableAntialiasedLine(bool enableDepthClip) {}
				void enableDepthClip(bool enableDepthClip) {}
				void enableMultisampling(bool enableMultisampling) {}
				void enableScissoring(bool enableScissoring) {}
				void setCullMode(RasterizerCullMode cullMode) {}
				void setDepthBias(AE::int32 depthBias) {}
				void setDepthBiasClamp(AE::Real depthBiasClamp) {}
				void setFillMode(RasterizerFillMode fillMode) {}
				void setFrontWhenCounterClockwise(bool frontWhenCounterClockwise) {}
				void setSlopeScaledDepthBias(AE::Real slopeScaledDepthBias) {}
				
				/***** Inherited from AE::Graphics::Device::Stage *****/
				void run();

			protected:
				AE::Graphics::Device::PipelineGL15 *mPipeline;

				/***** Inherited from AE::Graphics::Device::Stage
				AE::Graphics::Device::Subpipeline *mParentSubpipeline;
				AE::Graphics::Device::StageType mType;
				*****/
			};
		}
	}
}

#endif