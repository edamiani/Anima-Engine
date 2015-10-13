//#include "../include/AnimaOSProcessManagerWin32.h"
//#include "../include/AnimaOSProcessWin32.h"
#include "../include/AnimaOSEventQueueAllegro.h"
#include "../include/AnimaOSEvent.h"
#include "../include/AnimaOSWindowAllegro.h"
#include "../include/AnimaOSWindowManagerAllegro.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaInputKeyInfo.h"
#include <cassert>

namespace AE
{
	namespace OS
	{
		EventQueueAllegro::EventQueueAllegro() 
		{
			mAllegroEventQueue = al_create_event_queue();
		}

		EventQueueAllegro::~EventQueueAllegro()
		{
			al_destroy_event_queue(mAllegroEventQueue);
		}

		bool EventQueueAllegro::getNextEvent(AE::OS::Event *eventContainer)
		{
			bool success = al_get_next_event(mAllegroEventQueue, &mAllegroEvent);

			if(success)
			{
				_dispatchEvent(&mAllegroEvent);
				return true;
			}
			else
				return false;
		}

		bool EventQueueAllegro::peekNextEvent()
		{
			bool success = al_peek_next_event(mAllegroEventQueue, &mAllegroEvent);
			return success;
		}

		void EventQueueAllegro::registerWindowListener(AE::OS::WindowListener *windowListener)
		{
			mWindowListeners.push_back(windowListener);
		}

		bool EventQueueAllegro::waitNextEvent()
		{
			al_wait_for_event(mAllegroEventQueue, &mAllegroEvent);
			return true;
		}

		void EventQueueAllegro::_dispatchEvent(ALLEGRO_EVENT *allegroEvent)
		{
			if(allegroEvent->type > ALLEGRO_EVENT_DISPLAY_EXPOSE)
			{
				AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(allegroEvent->display.source);
				std::list<AE::OS::WindowListener *>::iterator i;

				switch(allegroEvent->type)
				{
				case ALLEGRO_EVENT_DISPLAY_CLOSE:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onClose(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_EXPOSE:
					{
						AE::Math::Point2 topLeft = AE::Math::Point2(allegroEvent->display.x, allegroEvent->display.y);
						AE::Math::Point2 dimensions = AE::Math::Point2(allegroEvent->display.width, allegroEvent->display.height);
						for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
							(*i)->onRestore(window, topLeft, dimensions);
						break;
					}

				case ALLEGRO_EVENT_DISPLAY_FOUND:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onDeviceFound(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_LOST:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onDeviceLost(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onOrientationChanged(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_RESIZE:
					{
						AE::Math::Point2 topLeft = AE::Math::Point2(allegroEvent->display.x, allegroEvent->display.y);
						AE::Math::Point2 dimensions = AE::Math::Point2(allegroEvent->display.width, allegroEvent->display.height);
						for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
							(*i)->onResize(window, topLeft, dimensions);
						break;
					}

				case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onGainFocus(window);
					break;

				case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
					for(i = mWindowListeners.begin(); i != mWindowListeners.end(); i++)
						(*i)->onLostFocus(window);
					break;
				}
			}
		}

		AE::OS::Event* EventQueueAllegro::_translateEvent(ALLEGRO_EVENT *event)
		{
			AE::OS::Event *translatedEvent;

			switch(event->type)
			{
			case ALLEGRO_EVENT_DISPLAY_CLOSE:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_CLOSE, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_EXPOSE:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					AE::Math::Point2 topLeft = AE::Math::Point2(event->display.x, event->display.y);
					AE::Math::Point2 dimensions = AE::Math::Point2(event->display.width, event->display.height);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_RESTORE, window, &topLeft, &dimensions);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_FOUND:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_DEVICE_FOUND, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_LOST:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_DEVICE_LOST, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_ORIENTATION:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_ORIENTATION_CHANGED, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_RESIZE:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					AE::Math::Point2 topLeft = AE::Math::Point2(event->display.x, event->display.y);
					AE::Math::Point2 dimensions = AE::Math::Point2(event->display.width, event->display.height);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_RESIZE, window, &topLeft, &dimensions);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_GAIN_FOCUS, window);
					break;
				}

			case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
				{
					AE::OS::Window *window = static_cast<AE::OS::WindowManagerAllegro *>(AE::OS::WindowManagerAllegro::getInstance())->_getWindow(event->display.source);
					translatedEvent = new AE::OS::EventWindow(AE::OS::EST_WINDOW_LOST_FOCUS, window);
					break;
				}

			case ALLEGRO_EVENT_JOYSTICK_AXIS:
				break;

			case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
				break;

			case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
				break;

			case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
				break;

			case ALLEGRO_EVENT_KEY_CHAR:
				break;

			case ALLEGRO_EVENT_KEY_DOWN:
				break;

			case ALLEGRO_EVENT_KEY_UP:
				break;

			case ALLEGRO_EVENT_MOUSE_AXES:
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
				break;

			case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
				break;

			case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
				break;

			case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
				break;

			case ALLEGRO_EVENT_MOUSE_WARPED:
				break;
			}

			return translatedEvent;
		}
	}
}