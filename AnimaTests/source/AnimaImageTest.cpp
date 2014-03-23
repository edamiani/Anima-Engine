#include "AnimaTestSuite.h"

#include "AnimaException.h"
#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceManagerGL15.h"
#include "AnimaGraphicsDevicePixelBuffer.h"
#include "AnimaGraphicsDevicePixelBufferFactory.h"
#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsFontFaceDesc.h"
#include "AnimaGraphicsFontFactory.h"
#include "AnimaGraphicsFontManagerFT.h"
#include "AnimaGraphicsImage.h"
#include "AnimaGraphicsImageFactory.h"
#include "AnimaGraphicsImageLoaderPNG.h"
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

void ExampleTestSuite::imageTest()
{
	AE::PluginManager *pluginManager = AE::PluginManager::initialize();

#ifdef AE_PLATFORM_WIN32
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerWin()));
#else
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()));
#endif
	pluginManager->getRoot()->attach(windowManager);

	assert(windowManager);
	windowManager->install(AE::NO_OPTIONS);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
	windowDesc.position = AE::Math::Point2<AE::int32>(100, 100);
	AE::OS::Window *window = windowManager->createWindow("Image Test", windowDesc, 0);

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

	/*AE::Graphics::ImageFactory *imageFactory = AE::Graphics::ImageFactory::initialize();
	AE::Graphics::ImageLoader *imageLoader = imageFactory->registerLoader(new AE::Graphics::ImageLoaderPNG(), AE::Graphics::IT_PNG);
	AE::Graphics::Image *image = imageFactory->loadImage("gandalf2_large.png", AE::Graphics::AT_SYSTEM_MEMORY);

	AE::Graphics::Font::Manager *fontManager = static_cast<AE::Graphics::Font::Manager *>(pluginManager->registerPlugin("fontManagerFT", new AE::Graphics::Font::ManagerFT()));
	fontManager->install(AE::NO_OPTIONS);
	AE::Graphics::Font::Factory *fontFactory = fontManager->getFontFactory();
	fontFactory->registerFontFile("arial.ttf", "Arial");

	AE::Graphics::Font::FaceDesc fontFaceDesc;
	fontFaceDesc.fontType = AE::Graphics::FT_TRUETYPE;
	fontFaceDesc.glyphDimensions.x = 32;
	fontFaceDesc.glyphDimensions.y = 32;
	fontFaceDesc.horizontalResolution = 72;
	fontFaceDesc.registeredFontName = "Arial";
	fontFaceDesc.verticalResolution = 72;

	AE::Graphics::Font::Face *arial32 = fontManager->createFontFace("arial32", fontFaceDesc);

	AE::Graphics::Device::ContextDesc contextDesc;
	contextDesc.dimensions = window->getDimensions();
	contextDesc.fullScreen = false;
	contextDesc.parentWindow = window;
	contextDesc.setColorBufferFormat(AE::Graphics::Device::CBF_R8G8B8A8);

	AE::Graphics::Device::Context *deviceContext = deviceDriver->createDeviceContext(contextDesc);

	window->show();

	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color white(255, 255, 255);
	AE::Graphics::Device::PixelBuffer *frameBuffer = deviceContext->getFrameBuffer();

	AE::Graphics::AxesConvention2d axesConvention(AE::Graphics::HD_LEFT_TO_RIGHT, AE::Graphics::VD_TOP_TO_BOTTOM);

	while(myWindowListener.isRunning())
	{
		deviceContext->beginRendering(green);

		frameBuffer->lock(AE::Graphics::LT_DISCARD);
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-100, -100));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(220, -100));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(540, -100));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-100, 140));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(220, 140));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(540, 140));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-100, 380));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(220, 380));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(540, 380));

			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-300, -300));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(220, -300));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(940, -300));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-300, 140));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-940, 140));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-300, 780));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(220, 780));
			frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-940, 780));

			arial32->print(frameBuffer, L"Go back to the shadow, flame of Udûn!", AE::Math::Point2(80, 350), white);
		frameBuffer->unlock();

		deviceContext->endRendering();

		eventQueue->getNextEvent(0);
	}

	pluginManager->shutdown();*/
}
