#ifndef __AE_OS_MOUSE_LISTENER__
#define __AE_OS_MOUSE_LISTENER__

namespace AE
{
	namespace OS
	{
		class MouseListener
		{
		public:
			MouseListener() {}
			virtual ~MouseListener() {}

			// Mouse events
			virtual void onButtonDown(const AE::OS::EventMouse &event) = 0;
			virtual void onButtonUp(const AE::OS::EventMouse &event) = 0;
			virtual void onMouseMove(const AE::OS::EventMouse &event) = 0;
		};
	}
}

#endif