#ifndef __AE_OS_WINDOW_OSX__
#define __AE_OS_WINDOW_OSX__


#include "AnimaOSWindow.h"
#include "AnimaMathPoint2.h"

//#import <Cocoa/Cocoa.h>

namespace AE
{
	namespace OS
	{
		struct  WindowOSXImpl;
		
		class WindowOSX : public Window
		{
		public:
			WindowOSX(const std::string &windowTitle, const AE::Math::Point2 &dimensions);
			~WindowOSX();

			void	close() {  }
			bool	dispatchNextMessage();
			size_t	getWindowHandle() { return 0; }
			bool	waitAndDispatchNextMessage();
			void	render() {}
			void	show() {}

			// Window events
			virtual void onClose() {  }
			virtual void onDestroy() {}
			virtual void onDisplayChange() {  }
			virtual void onMove() {  }
			virtual void onResize() {  }
			
		protected:
			AE::OS::WindowOSXImpl *mWindowOSXImpl;
		};
	}
}

#endif