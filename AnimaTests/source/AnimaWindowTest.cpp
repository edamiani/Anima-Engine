#include "AnimaTestSuite.h"

#include "Anima/AnimaException.h"
#include "Anima/Math/AnimaMathPoint2.h"
#include "Anima/OS/AnimaOSWindowListener.h"

#ifdef AE_PLATFORM_WIN32
#	include "Anima/OS/Win/AnimaOSWindowManagerWin.h"
#elif defined AE_PLATFORM_LINUX
#	include "AnimaOSWindowManagerLinux.h"
#endif

#include "Anima/AnimaPluginManager.h"

#include <cassert>

class MyWindowListener : public AE::OS::WindowListener
{
public:
	MyWindowListener() : mIsRunning(true) {}
	~MyWindowListener() {}

	bool isRunning() { return mIsRunning; }

	void onClose(AE::OS::Window *window)
	{
		mIsRunning = false;
	}

protected:
	bool mIsRunning;
};

void ExampleTestSuite::windowTest()
{
	AE::PluginManager *pluginManager = AE::PluginManager::initialize();

#ifdef AE_PLATFORM_WIN32
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerWin()));
#else
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()));
#endif

	assert(windowManager);
	pluginManager->getRoot()->attachAndInstall(windowManager, AE::NO_OPTIONS);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
	windowDesc.position = AE::Math::Point2<AE::int32>(0, 0);
	AE::OS::Window *window = windowManager->createWindow("Window Test", windowDesc);

	MyWindowListener *myWindowListener = new MyWindowListener();
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(myWindowListener);

	window->show();

	while(myWindowListener->isRunning())
	{
		eventQueue->getNextEvent(0);
	}

	windowManager->uninstall();

	pluginManager->shutdown();

	delete myWindowListener;
}
