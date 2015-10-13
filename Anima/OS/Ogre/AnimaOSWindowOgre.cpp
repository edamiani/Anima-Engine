#include "../include/AnimaOSWindowOgre.h"

namespace AE
{
	namespace OS
	{
		WindowOgre::WindowOgre(Ogre::RenderWindow *window, AE::Graphics::DeviceContext *deviceContext, const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, bool isFullScreen) 
			: mOgreWindow(window), Window(deviceContext, windowTitle, windowDesc)
		{
		}

		WindowOgre::~WindowOgre()
		{
			mOgreWindow = 0;
		}

		size_t WindowOgre::getWindowHandle()
		{
			size_t windowHnd = 0;
			mOgreWindow->getCustomAttribute("WINDOW", &windowHnd);
			return windowHnd;
		}

		/*WindowMetrics WindowOgre::getWindowMetrics()
		{
			unsigned int width, height, depth;
			int left, top;
			mOgreWindow->getMetrics(width, height, depth, left, top);
			return WindowMetrics(width, height, depth, top, left);
		}

		void WindowOgre::windowResized(Ogre::RenderWindow* rw)
		{
			unsigned int width, height, depth;
			int left, top;
			rw->getMetrics(width, height, depth, left, top);

			//const OIS::MouseState &ms = mMouse->getMouseState();
			//ms.width = width;
			//ms.height = height;

			mFramework->onWindowResized(getWindowMetrics());
		}*/
	}
}