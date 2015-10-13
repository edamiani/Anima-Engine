#ifndef __AE_GRAPHICS_DEVICE_STAGE_TRANSFORMATION2D_GL1_5__
#define __AE_GRAPHICS_DEVICE_STAGE_TRANSFORMATION2D_GL1_5__

#include "AnimaGraphicsDeviceTransformation2dGL1_5.h"

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class Subpipeline;

			class StageTransformation2d : public AE::Graphics::Device::Stage
			{
			public:
				StageTransformation2d(AE::Graphics::Device::StageType stageType, AE::Graphics::Device::Subpipeline *parentSubpipeline)
					: mType(stageType), mParentSubpipeline(parentSubpipeline) {}

				virtual ~Stage() {}

				void begin();
				void end();

				void rotate(AE::Graphics::Image, AE::Real angle);
				void scale(AE::Graphics::Image, const AE::Math::Point2 &scale);
				void setViewport(const AE::Math::Rectangle &viewport);
				void setWindow(const AE::Math::Rectangle &window);

			protected:
 
			};
		}
	}
}

#endif