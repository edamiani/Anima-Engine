#ifndef __AE_GRAPHICS_DEVICE_STAGE_CLIPPING_2D_GL1_5__
#define __AE_GRAPHICS_DEVICE_STAGE_CLIPPING_2D_GL1_5__

#include "AnimaGraphicsDeviceStageClipping2d.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageClipping2dGL1_5 : public AE::Graphics::Device::StageClipping2d
			{
			public:
				StageClipping2dGL1_5(AE::Graphics::Device::Subpipeline *parentSubpipeline);
				~StageClipping2dGL1_5();
				
				/***** Inherited from AE::Graphics::Device::Stage *****/
				void run();

			protected:
				/***** Inherited from AE::Graphics::Device::Stage *****
				AE::Graphics::Device::Subpipeline *mParentSubpipeline;
				AE::Graphics::Device::StageType mType;*/
			};
		}
	}
}

#endif