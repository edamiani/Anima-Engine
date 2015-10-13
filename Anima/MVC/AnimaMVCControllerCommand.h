#ifndef __AE_MVC_CONTROLLER_COMMAND__
#define __AE_MVC_CONTROLLER_COMMAND__

namespace AE
{
	namespace MVC
	{
		class ControllerCommand
		{
		public:
			ControllerCommand() {}
			virtual ~ControllerCommand() {}

			virtual void execute() = 0;
		};
	}
}

#endif