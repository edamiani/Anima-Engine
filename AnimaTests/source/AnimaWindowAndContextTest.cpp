#include "AnimaTestSuite.h"

#include "AnimaException.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceManagerGL1_5.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSWindowListener.h"
#include "AnimaPluginManager.h"

#ifdef AE_PLATFORM_WIN32
#	include "AnimaOSWindowManagerWin.h"
#elif defined AE_PLATFORM_LINUX
#	include "AnimaOSWindowManagerLinux.h"
#endif


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

void ExampleTestSuite::windowAndContextTest()
{
	AE::PluginManager *pluginManager = AE::PluginManager::initialize();

#ifdef AE_PLATFORM_WIN32
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerWin()));
#else
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()));
#endif

	assert(windowManager);
	windowManager->install(0);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2(640, 480);
	windowDesc.position = AE::Math::Point2(100, 100);
	AE::OS::Window *window = windowManager->createWindow("Window Test", windowDesc, 0);

	MyWindowListener myWindowListener;
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(&myWindowListener);

	AE::Graphics::Device::Manager *deviceManager;
	AE::Graphics::Device::Driver *deviceDriver;

#ifdef AE_PLATFORM_WIN32
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL1_5", new AE::Graphics::Device::ManagerGL1_5()));
	deviceManager->install(0);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_OPENGL1_5);
#else
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL1_5", new AE::Graphics::Device::ManagerGL1_5()));
	deviceManager->install(0);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_OPENGL1_5);
#endif

	AE::Graphics::Device::ContextDesc contextDesc;
	contextDesc.dimensions = window->getDimensions();
	contextDesc.fullScreen = false;
	contextDesc.parentWindow = window;
	contextDesc.setSurfaceFormat(AE::Graphics::SF_R8G8B8A8);

	AE::Graphics::Device::Context *deviceContext = deviceDriver->createDeviceContext(contextDesc);

	window->show();

	AE::Graphics::Color red(255, 0, 0);

	while(myWindowListener.isRunning())
	{
		eventQueue->getNextEvent(0);

		deviceContext->beginRendering(red);

		deviceContext->endRendering();
	}

	pluginManager->shutdown();
}
