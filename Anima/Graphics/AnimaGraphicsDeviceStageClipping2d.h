#ifndef __AE_GRAPHICS_DEVICE_STAGE_CLIPPING_2D__
#define __AE_GRAPHICS_DEVICE_STAGE_CLIPPING_2D__

#include "AnimaGraphicsDeviceStage.h"

#include "AnimaGraphicsEnums.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Subpipeline;

			class StageClipping2d : public AE::Graphics::Device::Stage
			{
			public:
				StageClipping2d(AE::Graphics::Device::Subpipeline *parentSubpipeline) : Stage(AE::Graphics::Device::ST_CLIPPING_2D, parentSubpipeline) {}
				virtual ~StageClipping2d() {}

				/***** Inherited from AE::Graphics::Device::Stage *****
				virtual void run() = 0;*/

			protected:
				/***** Inherited from AE::Graphics::Device::Stage *****
				AE::Graphics::Device::Subpipeline *mParentSubpipeline;
				AE::Graphics::Device::StageType mType;*/
			};
		}
	}
}

#endif