#ifndef __AE_GRAPHICS_DEVICE_PIPELINE_STAGE__
#define __AE_GRAPHICS_DEVICE_PIPELINE_STAGE__

#include "Anima/Graphics/AnimaGraphicsEnums.h"

#include <string>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class PipelineStage
			{
			public:
				PipelineStage() {}
				virtual ~PipelineStage() {}

			protected:
				AE::Graphics::Device::StageType mType;
			};
		}
	}
}

#endif