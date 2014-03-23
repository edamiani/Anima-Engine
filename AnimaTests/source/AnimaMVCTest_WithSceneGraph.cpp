#include "../include/AnimaMVCTest_WithSceneGraph.h"
#include "../include/AnimaGraphicsManager.h"
#include "../include/AnimaGraphicsCamera2d.h"
#include "../include/AnimaSceneFactoryX3D.h"
#include "../include/AnimaSceneGraphX3D.h"

#ifdef AE_PLATFORM_WIN32
	#include "AnimaMVCFrontControllerFSMWin32.h"
#elif defined(AE_PLATFORM_OSX)
	#include "AnimaMVCFrontControllerFSMOSX.h"
#endif

#ifdef AE_PLATFORM_WIN32
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
#else
int main()
#endif
{
	srand((unsigned int)time(NULL));

	AE::OS::WindowMetrics windowMetrics;
	windowMetrics.setSurfaceFormat(AE::Graphics::SF_A8R8G8B8);
	windowMetrics.top = 100;
	windowMetrics.left = 100;
	windowMetrics.width = 800;
	windowMetrics.height = 600;

#ifdef AE_PLATFORM_WIN32
	#if USING_OPENGL == 1
		AE::MVC::FrontControllerFSMWin32 *controller = new AE::MVC::FrontControllerFSMWin32("test", windowMetrics, false, true, AE::Graphics::RT_OPENGL);
	#elif USING_OPENGL == 0
		AE::MVC::FrontControllerFSMWin32 *controller = new AE::MVC::FrontControllerFSMWin32("test", windowMetrics, false, true, AE::Graphics::RT_DIRECT3D9);
	#endif
#elif defined(AE_PLATFORM_OSX)
	AE::MVC::FrontControllerFSMOSX *controller = new AE::MVC::FrontControllerFSMOSX("test", windowMetrics, false, true, AE::Graphics::RT_OPENGL);
#endif
	
	MyModel *model = new MyModel(controller->getGraphicsManager());

	MyView *view = new MyView(controller->getGraphicsManager(), model);
	MyFrontControllerFSMState *state = new MyFrontControllerFSMState(FSM_STATE_MAIN, model, view);
	controller->addState(state);
	controller->setDefaultState(state);
	controller->execute();

	delete controller;

	return 0;
}