#ifndef __AE_GRAPHICS_DEVICE_PIPELINE__
#define __AE_GRAPHICS_DEVICE_PIPELINE__

#include "Anima/Graphics/Device/Stage.h"
#include "Anima/Graphics/Device/Subpipeline.h"

#include "Anima/Math/Matrix4.h"

#include <map>

namespace AE
{
	namespace Graphics
	{
		class ColorBuffer;

		//typedef std::pair<AE::Graphics::ColorBuffer *, AE::Math::Matrix4> TransformedColorBuffer;

		namespace Device
		{
			class Context;
			class Driver;

			class Pipeline
			{
			public:
				Pipeline(AE::Graphics::Device::Context *parentContext) : mParentContext(parentContext) {}
				virtual ~Pipeline();

				virtual AE::Graphics::Device::SubpipelinePtr		createSourceSubpipeline(AE::Graphics::Device::SubpipelineType subPipelineType) = 0;
				AE::Graphics::Device::Context*						getParentContext() { return mParentContext; }
				AE::Graphics::Device::Subpipeline*					getSubpipeline(AE::Graphics::Device::SubpipelineType subpipelineType);
				virtual void										render() = 0;

			protected:
				std::map<AE::Graphics::Device::SubpipelineType, AE::Graphics::Device::SubpipelinePtr>		
																	mSourceSubpipelines;
				AE::Graphics::Device::Context						*mParentContext;
			};
		}
	}
}

#endif