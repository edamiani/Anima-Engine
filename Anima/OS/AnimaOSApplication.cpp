#include "Anima/AnimaPlatform.h"
#include "Anima/OS/AnimaOSApplication.h"

#ifdef AE_PLATFORM_WIN32
	#include "OS/Win32/AnimaOSApplicationWin32.h"
	//#include "../include/AnimaGraphicsManagerDX9.h"
	//#include "../include/AnimaGraphicsManagerGL.h"
#endif

AE::OS::Application* AE::OS::Application::mInstance = 0;

namespace AE
{
	namespace OS
	{
		AE::OS::Application* Application::initialize(AE::Graphics::RenderType renderType)
		{
		#ifdef AE_PLATFORM_WIN32
			mInstance = new AE::OS::ApplicationWin32();
			//switch(renderType)
			//{
			//case AE::Graphics::RT_DIRECT3D9:
			//	//new AE::Graphics::ManagerDX9();
			//	break;
			//case AE::Graphics::RT_OPENGL:
			//	//new AE::Graphics::ManagerGL();
			//	break;
			//default:
			//	break;
			//}
		#endif

			return mInstance;
		}

		void Application::shutdown()
		{
			/*if(AE::Graphics::Manager::getInstance())
				delete AE::Graphics::Manager::getInstance();*/

			delete mInstance;
		}
	}
}