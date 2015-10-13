#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL1_5_COCOA__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL1_5_COCOA__

#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceContextDesc.h"
#include "AnimaGraphicsSurfaceGL1_5.h"
#include "AnimaOSWindow.h"
#include "AnimaPlatform.h"

#import "AnimaGraphicsDeviceContextCocoaImpl.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL1_5 : public AE::Graphics::Device::Context
			{
			public:
				ContextGL1_5(AE::Graphics::Device::ContextDesc &contextDesc, AE::Graphics::Device::Driver *deviceDriver);
				virtual ~ContextGL1_5();

				bool beginRendering();
				bool beginRendering(const AE::Graphics::Color &clearColor);
				//AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
				AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory);
				void endRendering();
				void render();

			protected:
#			if AE_PLATFORM_OSX_MAJOR_VERSION < 10
				//AGLContext mAGLContext;
#			else
				AnimaGraphicsDeviceContextCocoaImpl *mDeviceContextCocoa;
#           endif
			};
		}
	}
}

#endif