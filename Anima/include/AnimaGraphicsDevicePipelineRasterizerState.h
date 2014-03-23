#ifndef __AE_GRAPHICS_DEVICE_PIPELINE_RASTERIZER_STATE__
#define __AE_GRAPHICS_DEVICE_PIPELINE_RASTERIZER_STATE__

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
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

			class PipelineRasterizerState
			{
			public:
				PipelineRasterizerState() {}
				virtual ~PipelineRasterizerState() {}

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

			protected:
			};
		}
	}
}

#endif