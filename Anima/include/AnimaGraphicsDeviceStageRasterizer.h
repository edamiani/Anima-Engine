#ifndef __AE_GRAPHICS_DEVICE_STAGE_RASTERIZER__
#define __AE_GRAPHICS_DEVICE_STAGE_RASTERIZER__

#include "AnimaGraphicsDeviceStage.h"

#include "AnimaGraphicsEnums.h"
#include "AnimaTypes.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class FrameBuffer;

			enum RasterizerCullMode
			{
				RCM_BACK,
				RCM_FRONT,
				RCM_NONE
			};

			enum RasterizerFillMode
			{
				RFM_SOLID,
				RFM_WIREFRAME
			};

			class StageRasterizer : public AE::Graphics::Device::Stage
			{
			public:
				StageRasterizer(AE::Graphics::Device::Subpipeline *parentSubpipeline, AE::Graphics::Device::FrameBuffer *frameBuffer) 
					: Stage(AE::Graphics::Device::ST_RASTERIZER, parentSubpipeline), mFrameBuffer(frameBuffer) {}

				StageRasterizer(std::list<AE::Graphics::Device::Subpipeline *> &parentSubpipelines, AE::Graphics::Device::FrameBuffer *frameBuffer)
					: Stage(AE::Graphics::Device::ST_RASTERIZER, parentSubpipelines), mFrameBuffer(frameBuffer) {}

				virtual ~StageRasterizer() {}

				virtual void enableAntialiasedLine(bool enableDepthClip) = 0;
				virtual void enableDepthClip(bool enableDepthClip) = 0;
				virtual void enableMultisampling(bool enableMultisampling) = 0;
				virtual void enableScissoring(bool enableScissoring) = 0;
				virtual void setCullMode(RasterizerCullMode cullMode) = 0;
				virtual void setDepthBias(AE::int32 depthBias) = 0;
				virtual void setDepthBiasClamp(AE::Real depthBiasClamp) = 0;
				virtual void setFillMode(RasterizerFillMode fillMode) = 0;
				virtual void setFrontWhenCounterClockwise(bool frontWhenCounterClockwise) = 0;
				virtual void setSlopeScaledDepthBias(AE::Real slopeScaledDepthBias) = 0;

				/***** Inherited from AE::Graphics::Device::Stage
				virtual void run() = 0;
				*****/

			protected:
				AE::Graphics::Device::FrameBuffer	*mFrameBuffer;

				/***** Inherited from AE::Graphics::Device::Stage
				AE::Graphics::Device::Subpipeline	*mParentSubpipeline;
				AE::Graphics::Device::StageType		mType;
				*****/
			};
		}
	}
}

#endif