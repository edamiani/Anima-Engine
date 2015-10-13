#ifndef __AE_OS_WINDOW_OGRE__
#define __AE_OS_WINDOW_OGRE__

#include "AnimaOSWindow.h"

#include "Ogre.h"

namespace AE
{
	namespace OS
	{
		class WindowOgre : public Window
		{
		public:
			WindowOgre(Ogre::RenderWindow *window, AE::Graphics::DeviceContext *deviceContext, const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc, bool isFullScreen = false);
			~WindowOgre();

			void	close() { }
			size_t	getWindowHandle();
			void	show() { }

		private:
			Ogre::RenderWindow		*mOgreWindow;
		};
	}
}

#endif