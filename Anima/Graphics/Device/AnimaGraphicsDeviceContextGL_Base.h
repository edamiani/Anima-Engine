#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL_BASE__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL_BASE__

#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"

#include "Anima/AnimaPlatform.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContextDesc.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceGLHeaders.h"
#include "Anima/OS/AnimaOSWindow.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL_Base : public AE::Graphics::Device::Context
			{
			public:
				ContextGL_Base(AE::Graphics::Device::Driver *deviceDriver);
				virtual ~ContextGL_Base();

				bool beginRendering();
				bool beginRendering(const AE::Graphics::Color &clearColor);
				//AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
				//AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory);
				void draw3dObject(AE::Graphics::RenderOperationType operationType, AE::Graphics::Device::VertexBuffer *vertexBuffer);
				void endRendering();
				void render();
				virtual void setFullScreen(bool isFullScreen) = 0;
				virtual void setParentWindow(AE::OS::Window *parentWindow) = 0;
			};
		}
	}
}

#endif