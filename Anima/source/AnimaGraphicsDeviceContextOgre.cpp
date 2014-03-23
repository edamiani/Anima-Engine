#include "../include/AnimaGraphicsDeviceContextOgre.h"

#include "../include/AnimaGraphicsSurfaceOgre.h"

#include "Ogre.h"

#ifdef OGRE_STATIC_LIB
#	include "RenderSystems/GL/include/OgreGLPlugin.h"
#	ifdef AE_PLATFORM_WIN32
#		include "RenderSystems/Direct3D9/include/OgreD3D9Plugin.h"
#	endif
#endif

#include <cassert>
#include <string>

namespace AE
{
	namespace Graphics
	{
		DeviceContextOgre::DeviceContextOgre(AE::Graphics::Device *graphicsDevice, const AE::Math::Point2 &dimensions, AE::Graphics::DeviceContextOption deviceContextOptions) 
			: mGraphicsDevice(graphicsDevice), mOgreRenderSystemPlugin(0)
		{
			Ogre::Root *ogreRoot = Ogre::Root::getSingletonPtr();

#		ifdef OGRE_STATIC_LIB
			if(deviceContextOptions & AE::Graphics::DCO_DX9)
				mOgreRenderSystemPlugin = OGRE_NEW Ogre::D3D9Plugin();
			else if(deviceContextOptions & AE::Graphics::DCO_OPENGL)
				mOgreRenderSystemPlugin = OGRE_NEW Ogre::GLPlugin();
			else
				mOgreRenderSystemPlugin = OGRE_NEW Ogre::GLPlugin();

			ogreRoot->installPlugin(mOgreRenderSystemPlugin);
#		else
#		ifdef _DEBUG
			if(deviceContextOptions & AE::Graphics::DCO_OPENGL)
				ogreRoot->loadPlugin("RenderSystem_GL_d");
			else if(deviceContextOptions & AE::Graphics::DCO_DX9)
				ogreRoot->loadPlugin("RenderSystem_Direct3D9_d");
			else
				ogreRoot->loadPlugin("RenderSystem_GL_d");
#		else
			if(deviceContextOptions & AE::Graphics::DCO_OPENGL)
				ogreRoot->loadPlugin("RenderSystem_GL");
			else if(deviceContextOptions & AE::Graphics::DCO_DX9)
				ogreRoot->loadPlugin("RenderSystem_Direct3D9");
			else
				ogreRoot->loadPlugin("RenderSystem_GL");
#		endif
#		endif

			Ogre::RenderSystem *ogreRenderSystem = ogreRoot->getRenderSystemByName(mOgreRenderSystemPlugin->getName());
			//ogreRoot->setRenderSystem(ogreRenderSystem);
			graphicsDevice->initialize(0);
			//ogreRenderSystem->getDisplayMonitorCount(

				//al_set_new_display_flags(ALLEGRO_DIRECT3D_INTERNAL);
			/*else if(deviceContextOptions & AE::Graphics::DCO_OPENGL3)
				al_set_new_display_flags(ALLEGRO_OPENGL_3_0);
			else
				al_set_new_display_flags(ALLEGRO_OPENGL);

			mAllegroDisplay = al_create_display(dimensions.x, dimensions.y);
			mBackBuffer = new AE::Graphics::SurfaceAllegro(al_get_backbuffer(mAllegroDisplay));*/
		}

		DeviceContextOgre::~DeviceContextOgre()
		{
#		ifdef OGRE_STATIC_LIB
			mOgreRenderSystemPlugin->shutdown();

			if(mOgreRenderSystemPlugin)
				OGRE_DELETE mOgreRenderSystemPlugin;
#		endif
			//al_destroy_display(mAllegroDisplay);
		}

		/*AE::uint DeviceContextAllegro::createDrawingContext(AE::Graphics::SurfaceFormat surfaceFormat)
		{
			return 0;
		}*/

		bool DeviceContextOgre::beginRendering()
		{
			//al_set_target_backbuffer(mAllegroDisplay);
			return true;
		}

		bool DeviceContextOgre::beginRendering(const AE::Graphics::Color &clearColor)
		{
			//al_set_target_backbuffer(mAllegroDisplay);
			//al_clear_to_color(al_map_rgb(clearColor.R, clearColor.G, clearColor.B));
			return true;
		}

		AE::Graphics::Surface* DeviceContextOgre::createOffscreenSurface(const AE::Math::Point2 &dimensions, AE::Graphics::SurfaceFormat surfaceFormat, bool usesVideoMemory)
		{
			/*if(usesVideoMemory)
			{
				al_set_target_backbuffer(mAllegroDisplay);
				al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
			}
			else
				al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);

			ALLEGRO_BITMAP *allegroSurface = al_create_bitmap(dimensions.x, dimensions.y);
			AE::Graphics::Surface *newSurface = new AE::Graphics::SurfaceAllegro(allegroSurface);

			return newSurface;*/

			return 0;
		}

		void DeviceContextOgre::endRendering()
		{
			//al_flip_display();
		}

		void DeviceContextOgre::render()
		{
		}
	}
}