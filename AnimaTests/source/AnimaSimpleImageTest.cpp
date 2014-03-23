#include "AnimaTestSuite.h"

#include "AnimaException.h"
#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceManagerGL1_5.h"
#include "AnimaGraphicsDeviceFrameBuffer.h"
#include "AnimaGraphicsDevicePixelBuffer.h"
#include "AnimaGraphicsDevicePixelBufferFactory.h"
#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsFontFaceDesc.h"
#include "AnimaGraphicsFontFactory.h"
#include "AnimaGraphicsFontManagerFT.h"
#include "AnimaGraphicsManager.h"
#include "AnimaGraphicsImage.h"
#include "AnimaGraphicsImageFactory.h"
#include "AnimaGraphicsImageManager.h"
#include "AnimaMathPoint2.h"
#include "AnimaMathRectangle.h"
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

void ExampleTestSuite::simpleImageTest()
{
	AE::PluginManager *pluginManager = AE::PluginManager::initialize();

#ifdef AE_PLATFORM_WIN32
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(
		pluginManager->getRoot()->attachAndInstall(
			pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerWin()),
			AE::NO_OPTIONS
		)
	);
#else
	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(
		pluginManager->getRoot()->attachAndInstall(
			pluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()),
			AE::NO_OPTIONS
		)
	);
#endif	

	AE::Graphics::Manager *graphicsManager = static_cast<AE::Graphics::Manager *>(
		pluginManager->getRoot()->attachAndInstall(
			pluginManager->registerPlugin("graphicsManager", new AE::Graphics::Manager()),
			AE::Graphics::GMO_GL15 | AE::Graphics::GMO_IMAGE_PNG
		)
	);

	AE::OS::WindowDesc windowDesc;
	windowDesc.deviceDriverNumber = 0;
	windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
	windowDesc.fullScreen = false;
	windowDesc.position = AE::Math::Point2<AE::int32>(100, 100);
	windowDesc.setColorFormat(AE::Graphics::CF_R8G8B8A8);
	AE::OS::Window *window = windowManager->createWindow("Image Test", windowDesc, 0);
	window->show();

	MyWindowListener myWindowListener;
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(&myWindowListener);

	AE::Graphics::Device::Manager *deviceManager = AE::Graphics::Device::Manager::getInstance();
	AE::Graphics::Device::Driver *deviceDriver = deviceManager->getDeviceDriver(0);
	AE::Graphics::Device::Context *deviceContext = deviceDriver->getDeviceContext(0);
	AE::Graphics::Device::FrameBuffer *frameBuffer = deviceContext->getFrameBuffer();
	
	AE::Graphics::ImageManager *imageManager = graphicsManager->getImageManager();
	AE::Graphics::Image *gandalf = imageManager->createImage("gandalf", "gandalf2_large.png");

	AE::Graphics::Device::PixelBufferDesc pixelBufferDesc;
	pixelBufferDesc.colorBufferDesc = gandalf->getDesc().colorBufferDesc;
	pixelBufferDesc.colorFormatConversion = frameBuffer->getColorFormat();

	AE::Graphics::Device::PixelBuffer *pbGandalf = deviceManager->getPixelBufferFactory()->createPixelBuffer(pixelBufferDesc);

	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color white(255, 255, 255);

	AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_TOP_TO_BOTTOM;

	while(myWindowListener.isRunning())
	{
		deviceContext->beginRendering(green);

		frameBuffer->lock(AE::Graphics::LT_DISCARD);

		frameBuffer->blitFrom(pbGandalf, AE::Math::Point2<AE::uint>(0, 0), AE::Math::Point2<AE::uint>(pbGandalf->getDimensions().x, pbGandalf->getDimensions().y), AE::Math::Point2<AE::int32>(-100, 0));

		frameBuffer->unlock();

		deviceContext->endRendering();

		eventQueue->getNextEvent(0);
	}

	deviceManager->getPixelBufferFactory()->destroyPixelBuffer(pbGandalf);

	AE::PluginManager::shutdown();
}
