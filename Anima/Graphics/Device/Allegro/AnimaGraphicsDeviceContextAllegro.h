#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_ALLEGRO__
#define __AE_GRAPHICS_DEVICE_CONTEXT_ALLEGRO__

#include "AnimaGraphicsDeviceManagerAllegro.h"
#include "AnimaGraphicsDeviceContext.h"
//#include "AnimaGraphicsSurfaceDX9.h"
//#include "AnimaGraphicsDrawingContextDesc.h"
//#include "AnimaGraphicsDrawingContextDX9.h"

#include "allegro5/allegro.h"

#include <vector>

namespace AE
{
	namespace OS
	{
		class Window;
	}

	namespace Graphics
	{
		namespace Device
		{
			class ContextAllegro : public AE::Graphics::Device::Context
			{
			public:
				ContextAllegro(AE::Graphics::Device::Driver *deviceDriver, AE::OS::Window *window);
				virtual ~ContextAllegro();

				bool beginRendering();
				bool beginRendering(const AE::Graphics::Color &clearColor);
				//AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
				AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory = true);
				void endRendering();
				void render();

				ALLEGRO_DISPLAY* _getAllegroDisplay() { return mAllegroDisplay; }
				HGLRC& _getWinGlContext() { return mWinGlContext; }

			protected:
				ALLEGRO_DISPLAY *mAllegroDisplay;
				HGLRC mWinGlContext;
			};
		}
	}
}

#endif