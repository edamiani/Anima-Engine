#ifndef __AE_GRAPHICS_DEVICE_STAGE_INPUT2D__
#define __AE_GRAPHICS_DEVICE_STAGE_INPUT2D__

#include "AnimaGraphicsDeviceIndexBuffer.h"
#include "AnimaGraphicsDeviceStage.h"
#include "AnimaGraphicsDeviceSubpipeline.h"
#include "AnimaGraphicsDeviceVertexBuffer.h"

#include "Anima/Graphics/AnimaGraphicsColorBuffer.h"
#include "Anima/Graphics/AnimaGraphicsEnums.h"
#include "Anima/Math/AnimaMathMatrix4.h"
#include "Anima/Math/AnimaMathPoint2.h"

namespace AE
{
	namespace Graphics
	{
		class ColorBuffer;

		namespace Device
		{
			class StageInput2d : public AE::Graphics::Device::Stage
			{
			public:
				StageInput2d(AE::Graphics::Device::Subpipeline *parentSubpipeline) : Stage(AE::Graphics::Device::ST_INPUT_2D, parentSubpipeline) {}
				virtual ~StageInput2d() {}

				virtual void enqueueColorBuffer(AE::Graphics::ColorBuffer *colorBuffer) = 0;
				//virtual void enqueueIndexBuffer(AE::Graphics::Device::IndexBuffer *indexBuffer) = 0;
				virtual void enqueueTransformedColorBuffer(AE::Graphics::ColorBuffer *colorBuffer, AE::Math::Matrix4 const &modelMatrix, bool resetModelMatrix) = 0;
				//virtual void enqueueVertexBuffer(AE::Graphics::Device::VertexBuffer *vertexBuffer) = 0;

				/***** Inherited from AE::Graphics::Device::Stage
				virtual void run() = 0;
				*****/

			protected:
				/***** Inherited from AE::Graphics::Device::Stage
				AE::Graphics::Device::Subpipeline	*mParentSubpipeline;
				AE::Graphics::Device::StageType		mType;
				*****/
			};
		}
	}
}

#endif