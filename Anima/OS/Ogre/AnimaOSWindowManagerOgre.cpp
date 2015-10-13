#include "../include/AnimaOSWindowManagerOgre.h"

#include "../include/AnimaOSDeviceManager.h"
#include "../include/AnimaOSEventManagerOgre.h"
#include "../include/AnimaOSWindowOgre.h"

#if defined(AE_PLATFORM_ALLEGRO)
#	include "allegro5/allegro.h"
#	include "../include/AnimaGraphicsDeviceAllegro.h"
#	include "../include/AnimaGraphicsDeviceContextAllegro.h"
#else
#	include "../include/AnimaGraphicsDeviceOgre.h"
#	include "../include/AnimaGraphicsDeviceContextOgre.h"
#endif

#include "Ogre.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowManagerOgre::WindowManagerOgre() 
		{
			//al_set_new_display_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS);
		}

		WindowManagerOgre::~WindowManagerOgre()
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
				delete *i;
		}

		AE::OS::Window* WindowManagerOgre::createWindow(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, AE::Graphics::DeviceContextOption deviceContextOptions, AE::uint numVideoAdapter)
		{
			Ogre::Root *ogreRoot = Ogre::Root::getSingletonPtr();

#if defined(AE_PLATFORM_ALLEGRO)
			Ogre::NameValuePairList miscParams;

#	if defined(AE_PLATFORM_WIN32)
			if(numVideoAdapter >= static_cast<AE::uint>(al_get_num_video_adapters())) 
				al_set_new_display_adapter(0);
			else
				al_set_new_display_adapter(numVideoAdapter);

			AE::Graphics::Device *allegroDevice = AE::OS::DeviceManager::getInstance()->getGraphicsDevice(numVideoAdapter);

			AE::Graphics::DeviceContext *deviceContext = allegroDevice->createDeviceContext(windowDesc.dimensions, deviceContextOptions);
			al_set_window_title(static_cast<AE::Graphics::DeviceContextAllegro *>(deviceContext)->_getAllegroDisplay(), windowTitle.c_str());

			//AE::OS::EventManagerAllegro *eventManager = static_cast<AE::OS::EventManagerAllegro *>(AE::OS::EventManager::getInstance());
			//al_register_event_source(eventManager->_getAllegroEventQueue(), al_get_display_event_source(static_cast<AE::Graphics::DeviceContextAllegro *>(deviceContext)->_getAllegroDisplay()));

			//AE::OS::Window *window = new AE::OS::WindowAllegro(deviceContext, windowTitle, windowDesc);
			//mWindows.push_back(window);

			//size_t winHandle = reinterpret_cast<size_t>(al_get_win_window_handle(static_cast<AE::Graphics::DeviceContextAllegro *>(deviceContext)->_getAllegroDisplay()));
			//size_t winGlContext = reinterpret_cast<size_t>(static_cast<AE::Graphics::DeviceContextAllegro *>(deviceContext)->_getWinGlContext());
 
			//miscParams["externalWindowHandle"] = Ogre::StringConverter::toString(winHandle);
			//miscParams["externalGLContext"] = Ogre::StringConverter::toString(winGlContext);
#	else
			//miscParams["currentGLContext"] = Ogre::String("True");
#	endif
			//Ogre::RenderWindow *ogreRenderWindow = ogreRoot->createRenderWindow(windowTitle, windowDesc.dimensions.x, windowDesc.dimensions.y, windowDesc.fullScreen, &miscParams);
			//renderWindow->setVisible(true);
#endif

			/*AE::Graphics::Device *allegroDevice = AE::OS::DeviceManager::getInstance()->getGraphicsDevice(numVideoAdapter);

			AE::Graphics::DeviceContext *deviceContext = allegroDevice->createDeviceContext(windowDesc.dimensions, deviceContextOptions);
			al_set_window_title(static_cast<AE::Graphics::DeviceContextAllegro *>(deviceContext)->_getAllegroDisplay(), windowTitle.c_str());

			AE::OS::EventManagerAllegro *eventManager = static_cast<AE::OS::EventManagerAllegro *>(AE::OS::EventManager::getInstance());
			al_register_event_source(eventManager->_getAllegroEventQueue(), al_get_display_event_source(static_cast<AE::Graphics::DeviceContextAllegro *>(deviceContext)->_getAllegroDisplay()));

			AE::OS::Window *window = new AE::OS::WindowAllegro(deviceContext, windowTitle, windowDesc);
			mWindows.push_back(window);

			return window;*/

			return 0;
		}

		void WindowManagerOgre::destroyWindow(AE::OS::Window *window)
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				if(*i == window)
					delete window;
			}
		}

		/*AE::OS::Window* WindowManagerAllegro::_getWindow(ALLEGRO_DISPLAY* allegroDisplay)
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				AE::Graphics::DeviceContextAllegro *deviceContext = static_cast<AE::Graphics::DeviceContextAllegro *>((*i)->getDeviceContext());
				if(deviceContext->_getAllegroDisplay() == allegroDisplay)
					return *i;
			}

			return 0;
		}*/
	}
}