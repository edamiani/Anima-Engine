#ifndef __AE_MVC_CONTROLLER__
#define __AE_MVC_CONTROLLER__

namespace AE
{
	namespace MVC
	{
		class Controller
		{
		public:
			Controller() {}
			virtual ~Controller() {  }

			virtual void execute() = 0;
		};
	}
}

#endif