#ifndef __AE_OS_WINDOW_LISTENER__
#define __AE_OS_WINDOW_LISTENER__

#include "Anima/Math/Point2.h"
#include "Anima/OS/Window.h"

namespace AE
{
	namespace OS
	{
		class WindowListener
		{
		public:
			WindowListener() {}
			virtual ~WindowListener() {}

			// Window events
			virtual void onClose(AE::OS::Window *window) {}
			virtual void onDeviceFound(AE::OS::Window *window) {}
			virtual void onDeviceLost(AE::OS::Window *window) {}
			virtual void onGainFocus(AE::OS::Window *window) {}
			virtual void onLostFocus(AE::OS::Window *window) {}
			virtual void onOrientationChanged(AE::OS::Window *window) {}
			virtual void onResize(AE::OS::Window *window, const AE::Math::Point2<AE::int32> &topLeft, const AE::Math::Point2<AE::uint> &newDimensions) {}
			virtual void onRestore(AE::OS::Window *window, const AE::Math::Point2<AE::int32> &topLeft, const AE::Math::Point2<AE::uint> &dimensions) {}
		};
	}
}

#endif