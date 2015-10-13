#ifndef __AE_GRAPHICS_DEVICE_CONTEXT_OGRE__
#define __AE_GRAPHICS_DEVICE_CONTEXT_OGRE__

#include "../include/AnimaPlatform.h"

#include "AnimaGraphicsDeviceOgre.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDrawingContextDesc.h"

#include "Ogre.h"

#include <vector>

namespace AE
{
	namespace Graphics
	{
		class DeviceContextOgre : public AE::Graphics::Context
		{
		public:
			DeviceContextOgre(AE::Graphics::Device *graphicsDevice, const AE::Math::Point2 &dimensions, AE::Graphics::DeviceContextOption deviceContextOptions);
			virtual ~DeviceContextOgre();

			bool beginRendering();
			bool beginRendering(const AE::Graphics::Color &clearColor);
			AE::uint createDrawingContext(AE::OS::Window *window, AE::Graphics::SurfaceFormat surfaceFormat);
			AE::Graphics::Surface* createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory = true);
			void endRendering();
			void render();

			//ALLEGRO_DISPLAY* _getAllegroDisplay() { return mAllegroDisplay; }

		protected:
			//ALLEGRO_DISPLAY *mAllegroDisplay;
			AE::Graphics::Device *mGraphicsDevice;

#ifdef OGRE_STATIC_LIB
			Ogre::Plugin		*mOgreRenderSystemPlugin;
#endif
		};
	}
}

#endif