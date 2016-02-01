#ifndef __AE_GRAPHICS_DEVICE_STAGE_CLIPPING_2D_GL15__
#define __AE_GRAPHICS_DEVICE_STAGE_CLIPPING_2D_GL15__

#include "Anima/Graphics/Device/StageClipping2d.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class StageClipping2dGL15 : public AE::Graphics::Device::StageClipping2d
			{
			public:
				StageClipping2dGL15(AE::Graphics::Device::Subpipeline *parentSubpipeline);
				~StageClipping2dGL15();
				
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