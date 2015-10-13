#ifndef __AE_MVC_VIEW__
#define __AE_MVC_VIEW__

#include "AnimaMVCModel.h"

namespace AE
{
	namespace OS
	{
		class Window;
	}

	namespace MVC
	{
		class View
		{
		public:
			View(AE::OS::Window *window) : mWindow(window) {}
			virtual ~View() {  }

			virtual void render() = 0;

		protected:
			AE::OS::Window *mWindow;
		};
	}
}

#endif