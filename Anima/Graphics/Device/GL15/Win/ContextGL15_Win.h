#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_GL15_WIN__
#define __AE_GRAPHICS_DEVICE_CONTEXT_GL15_WIN__

#include "Anima/Graphics/Device/Context.h"

#include "Anima/Platform.h"
#include "Anima/Graphics/Device/ContextDesc.h"
#include "Anima/Graphics/Device/GL15/GLHeaders.h"
#include "Anima/OS/Window.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		namespace Device
		{
			class ContextGL15 : public AE::Graphics::Device::Context
			{
			public:
				ContextGL15(AE::Graphics::Device::ContextDesc &contextDesc, AE::Graphics::Device::Driver *deviceDriver);
				virtual ~ContextGL15();

				bool beginRendering();
				bool beginRendering(const AE::Graphics::Color &clearColor);
				//AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
				//AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory);
				void draw3dObject(AE::Graphics::RenderOperationType operationType, AE::Graphics::Device::VertexBuffer *vertexBuffer);
				void endRendering();
				void render();
				void setFullScreen(bool isFullScreen);
				void setParentWindow(AE::OS::Window *parentWindow);

			protected:
				void _setDeviceContext(HDC hdc) { mDeviceContextHandle = hdc; }

				HDC mDeviceContextHandle;
				HGLRC mRenderingContext;
			};
		}
	}
}

#endif