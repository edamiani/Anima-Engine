#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsFontFactory.h"
#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsImageFactory.h"
#include "AnimaGraphicsImage.h"
#include "AnimaGraphicsGeometryFactory.h"
#include "AnimaMathPoint2.h"
#include "AnimaOSConfig.h"
//#include "AnimaOSProcessManager.h"
#include "AnimaOSWindowListener.h"
#include "AnimaOSWindowManager.h"

#include "AnimaTestSuite.h"

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

void ExampleTestSuite::monitorAndVideoInfoTest()
{
	AE::OS::Config config(AE::OS::CO_FONT);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2(640, 480);
	windowDesc.position = AE::Math::Point2(100, 100);
	AE::OS::Window *window = AE::OS::WindowManagerAllegro::getInstance()->createWindow("Monitor and Video Info", windowDesc, AE::Graphics::Device::CO_DX9);

	MyWindowListener myWindowListener;
	AE::OS::EventManager *eventManager = AE::OS::EventManager::getInstance();
	eventManager->registerWindowListener(&myWindowListener);

	AE::Graphics::FontFactory *fontFactory = AE::Graphics::FontFactory::getInstance();
	AE::Graphics::FontFace *fontFace = fontFactory->createFontFace("arial.ttf", 0, 16, 0, 0, AE::Graphics::FO_MONOCHROME);

	AE::Graphics::Surface *backBuffer = window->getDeviceContext()->getBackBuffer();
	AE::Graphics::Color white(255, 255, 255);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color blue(0, 0, 255);
	
	while(myWindowListener.isRunning())
	{
		eventManager->getNextEvent(0);
		window->getDeviceContext()->beginRendering(white);

		fontFace->write("Monocromático", AE::Math::Point2(10, 130), black);	

		window->getDeviceContext()->endRendering();
	}

	fontFactory->destroyFontFace(fontFace);
}