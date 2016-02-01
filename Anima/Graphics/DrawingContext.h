#ifndef __AE_GRAPHICS_DRAWING_CONTEXT__
#define __AE_GRAPHICS_DRAWING_CONTEXT__

#include "Anima/Types.h"
#include "Anima/Graphics/Color.h"
#include "Anima/Graphics/Device/Context.h"
#include "Anima/Graphics/Surface.h"
#include "Anima/Math/Point2.h"

namespace AE
{
	namespace Graphics
	{
		class DrawingContext
		{
		public:
			DrawingContext(AE::Graphics::Device::Context *parentDeviceContext) : mFrameBuffer(), mParentDeviceContext(parentDeviceContext) {}
			virtual ~DrawingContext() {}

			AE::Graphics::Surface* getFrameBuffer() { return mFrameBuffer; }
			AE::Graphics::Device::Context* getParentDeviceContext() { return mParentDeviceContext; }
			void plot(const AE::Graphics::Color &color, const AE::Math::Point2 &position) { mFrameBuffer->plot(color, position); }

		protected:
			AE::Graphics::Surface *mFrameBuffer;
			AE::Graphics::Device::Context *mParentDeviceContext;
		};
	}
}

#endif