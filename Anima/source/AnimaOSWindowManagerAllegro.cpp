#include "../include/AnimaGraphicsDeviceManagerAllegro.h"

#include "../include/AnimaGraphicsDeviceContextAllegro.h"
#include "../include/AnimaGraphicsDeviceDriverAllegro.h"
#include "../include/AnimaOSEventQueueAllegro.h"
#include "../include/AnimaOSWindowManagerAllegro.h"
#include "../include/AnimaOSWindowAllegro.h"

#include <cassert>

namespace AE
{
	namespace OS
	{
		WindowManagerAllegro::WindowManagerAllegro() 
		{
			mInstance = this;
		}

		WindowManagerAllegro::~WindowManagerAllegro()
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
				delete *i;

			mInstance = 0;
		}

		bool WindowManagerAllegro::install(AE::uint options)
		{
			al_set_new_display_flags(ALLEGRO_GENERATE_EXPOSE_EVENTS);

			mEventQueue = new AE::OS::EventQueueAllegro();

			mIsInstalled = true;

			return true;
		}

		bool WindowManagerAllegro::uninstall()
		{
			delete mEventQueue;
			mEventQueue = 0;

			mIsInstalled = false;

			return true;
		}

		AE::OS::Window* WindowManagerAllegro::createWindow(const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, AE::Graphics::Device::Driver *deviceDriver)
		{
			if(deviceDriver->getDeviceId() >= static_cast<AE::uint>(al_get_num_video_adapters())) 
				al_set_new_display_adapter(0);
			else
				al_set_new_display_adapter(deviceDriver->getDeviceId());

			AE::OS::Window *window = new AE::OS::WindowAllegro(windowTitle, windowDesc);
			mWindows.push_back(window);

			AE::Graphics::Device::Context *deviceContext = deviceDriver->createDeviceContext(window);
			al_set_window_title(static_cast<AE::Graphics::Device::ContextAllegro *>(deviceContext)->_getAllegroDisplay(), windowTitle.c_str());

			AE::OS::EventQueueAllegro *eventQueue = static_cast<AE::OS::EventQueueAllegro *>(mEventQueue);
			al_register_event_source(eventQueue->_getAllegroEventQueue(), al_get_display_event_source(static_cast<AE::Graphics::Device::ContextAllegro *>(deviceContext)->_getAllegroDisplay()));

			return window;
		}

		void WindowManagerAllegro::destroyWindow(AE::OS::Window *window)
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				if(*i == window)
					delete window;
			}
		}

		AE::OS::Window* WindowManagerAllegro::_getWindow(ALLEGRO_DISPLAY* allegroDisplay)
		{
			std::list<AE::OS::Window *>::iterator i;
			for(i = mWindows.begin(); i != mWindows.end(); i++)
			{
				AE::Graphics::Device::ContextAllegro *deviceContext = static_cast<AE::Graphics::Device::ContextAllegro *>((*i)->getDeviceContext());
				if(deviceContext->_getAllegroDisplay() == allegroDisplay)
					return *i;
			}

			return 0;
		}
	}
}