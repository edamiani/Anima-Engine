#include "AnimaTestSuite.h"

#include "AnimaConsoleShell.h"
#include "AnimaException.h"
#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceFrameBuffer.h"
#include "AnimaGraphicsDeviceManagerGL15.h"
#include "AnimaGraphicsDevicePixelBuffer.h"
#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsFontFactory.h"
#include "AnimaGraphicsFontManagerFT.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSEvent.h"
#include "AnimaOSKeyListener.h"
#include "AnimaOSTimerManagerPoco.h"
#include "AnimaOSWindowListener.h"
#ifdef AE_PLATFORM_WIN32
#	include "AnimaOSWindowManagerWin.h"
#elif defined AE_PLATFORM_LINUX
#	include "AnimaOSWindowManagerLinux.h"
#endif
#include "AnimaPluginManager.h"

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

void ExampleTestSuite::consoleTest()
{
	AE::PluginManager *pluginManager = AE::PluginManager::initialize();

	AE::OS::TimerManager *timerManager = static_cast<AE::OS::TimerManager *>(pluginManager->registerPlugin("timerManager", new AE::OS::TimerManagerPoco()));
	pluginManager->getRoot()->attach(timerManager);

	assert(pluginManager);
	timerManager->install(AE::NO_OPTIONS);

#ifdef AE_PLATFORM_WIN32
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerWin()));
#elif defined AE_PLATFORM_LINUX
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()));
#endif
	pluginManager->getRoot()->attach(windowManager);

	assert(windowManager);
	windowManager->install(AE::NO_OPTIONS);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
	windowDesc.position = AE::Math::Point2<AE::int32>(100, 100);
	AE::OS::Window *window = windowManager->createWindow("Console Test", windowDesc, 0);

	MyWindowListener myWindowListener;
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(&myWindowListener);

	AE::Graphics::Device::Manager *deviceManager;
	AE::Graphics::Device::Driver *deviceDriver;

#ifdef AE_PLATFORM_WIN32
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	pluginManager->getRoot()->attach(deviceManager);
	deviceManager->install(AE::NO_OPTIONS);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_GL_15);
#else
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	pluginManager->getRoot()->attach(deviceManager);
	deviceManager->install(AE::NO_OPTIONS);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_OPENGL1_5);
#endif

	AE::Graphics::Font::Manager *fontManager = static_cast<AE::Graphics::Font::Manager *>(pluginManager->registerPlugin("fontManagerFT", new AE::Graphics::Font::ManagerFT()));
	fontManager->install(AE::NO_OPTIONS);
	AE::Graphics::Font::Factory *fontFactory = fontManager->getFontFactory();
	fontFactory->registerFontFile("courier.ttf", "Courier");

	AE::Graphics::Font::FaceDesc fontFaceDesc;
	fontFaceDesc.fontType = AE::Graphics::FT_TRUETYPE;
	fontFaceDesc.glyphDimensions.x = 16;
	fontFaceDesc.glyphDimensions.y = 16;
	fontFaceDesc.horizontalResolution = 72;
	fontFaceDesc.verticalResolution = 72;

	//AE::Graphics::Font::Face *arial16 = fontFactory->createFontFace("Courier", fontFaceDesc);

	AE::Graphics::Device::ContextDesc contextDesc;
	contextDesc.dimensions = window->getDimensions();
	contextDesc.fullScreen = false;
	contextDesc.parentWindow = window;
	contextDesc.setColorFormat(AE::Graphics::CF_R8G8B8A8);

	AE::Graphics::Device::Context *deviceContext = deviceDriver->createDeviceContext(contextDesc);

	window->show();

	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color white(255, 255, 255);
	AE::Graphics::Device::FrameBuffer *frameBuffer = deviceContext->getFrameBuffer();

	AE::Graphics::AxesConvention2d::horizontalDirection = AE::Graphics::HD_LEFT_TO_RIGHT;
	AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_BOTTOM_TO_TOP;

	AE::ConsoleDesc consoleDesc;
	consoleDesc.backgroundColor = black;
	consoleDesc.caretCharacter = '_';
	consoleDesc.colorFormat = AE::Graphics::CF_R8G8B8A8;
	consoleDesc.consoleStyle = AE::CS_LINE_ORIENTED;
	consoleDesc.dimensionsInCharacters = AE::Math::Point2<AE::uint>(80, 25);
	consoleDesc.dimensionsInPixels = AE::Math::Point2<AE::uint>(640, 480);
	consoleDesc.foregroundColor = white;
	consoleDesc.registeredFontName = "Courier";
	AE::Console *console = new AE::ConsoleShell(consoleDesc);

	while(myWindowListener.isRunning())
	{
		deviceContext->beginRendering(green);

		frameBuffer->lock(AE::Graphics::LT_DISCARD);
			console->render(frameBuffer);
			//frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(10, 10));
			//arial16->print(frameBuffer, "Go back to the shadow, flame of Udun!", AE::Math::Point2(80, 350), white);
		frameBuffer->unlock();

		deviceContext->endRendering();

		eventQueue->getNextEvent(0);
	}

	delete console;

	pluginManager->shutdown();
}
