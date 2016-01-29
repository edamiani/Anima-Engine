#include "AnimaTestSuite.h"

#include "Anima/AnimaException.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceDriver.h"
//#include "Anima/Graphics/Device/GL15/AnimaGraphicsDeviceManagerGL15.h"
#include "Anima/Graphics/Device/GL15/Sdl/AnimaGraphicsDeviceManagerGL15_Sdl.h"
#include "Anima/Math/AnimaMathPoint2.h"
#include "Anima/OS/AnimaOSWindowListener.h"
#include "Anima/AnimaPluginManager.h"

#ifdef AE_PLATFORM_WIN32
#	include "Anima/OS/Sdl/WindowManagerSdl.h"
#elif defined AE_PLATFORM_LINUX
#	include "AnimaOSWindowManagerLinux.h"
#endif


#include <cassert>

class WindowAndContextListener : public AE::OS::WindowListener
{
public:
	WindowAndContextListener() : mIsRunning(true) {}
	~WindowAndContextListener() {}

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
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerSdl()));
#else
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()));
#endif

	assert(windowManager);
	pluginManager->getRoot()->attachAndInstall(windowManager, AE::NO_OPTIONS);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
	windowDesc.position = AE::Math::Point2<AE::int32>(100, 100);

	AE::OS::Window *window = windowManager->createWindow("Window Test", windowDesc);

	WindowAndContextListener myWindowListener;
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(&myWindowListener);

	AE::Graphics::Device::Manager *deviceManager;
	AE::Graphics::Device::Driver *deviceDriver;

#ifdef AE_PLATFORM_WIN32
	//deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerSDL", new AE::Graphics::Device::ManagerGL15()));
	pluginManager->getRoot()->attachAndInstall(deviceManager, AE::NO_OPTIONS);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_GL_15);
#else
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	pluginManager->getRoot()->attachAndInstall(deviceManager, AE::NO_OPTIONS);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_OPENGL1_5);
#endif

	AE::Graphics::Device::ContextDesc contextDesc;
	contextDesc.dimensions = window->getDimensions();
	contextDesc.fullScreen = false;
	contextDesc.parentWindow = window;

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
