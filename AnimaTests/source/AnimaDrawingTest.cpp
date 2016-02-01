#include "AnimaTestSuite.h"

#include "Anima/Exception.h"
#include "Anima/Graphics/DeviceManager.h"
#include "Anima/Graphics/Enums.h"
#include "Anima/Graphics/FontFactory.h"
#include "Anima/Graphics/FontFace.h"
#include "Anima/Graphics/ImageFactory.h"
#include "Anima/Graphics/Image.h"
#include "Anima/Graphics/GeometryFactory.h"
#include "Anima/Math/Point2.h"
#include "Anima/OS/Config.h"
//#include "Anima/OS/ProcessManager.h"
#include "Anima/OS/WindowListener.h"
#include "Anima/OS/WindowManager.h"
#include "Anima/PluginManager.h"

#include "AnimaPluginGroupAllegro.h"

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

void ExampleTestSuite::drawingTest()
{
	AE::PluginManager *pluginManager = AE::PluginManager::initialize();
	
	AE::PluginGroup *pluginGroupAllegro = static_cast<AE::PluginGroup *>(pluginManager->getRoot()->attach("pluginGroupAllegro", new AE::PluginGroupAllegro()));
	assert(pluginGroupAllegro);

	AE::OS::WindowManager *windowManager;
	AE::Graphics::Device::Manager *graphicsDeviceManager;
	try
	{
		windowManager = static_cast<AE::OS::WindowManager *>(pluginGroupAllegro->createPlugin("windowManagerAllegro", AE::PT_OS_WINDOW_MANAGER));
		graphicsDeviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginGroupAllegro->createPlugin("graphicsDeviceManagerAllegro", AE::PT_GRAPHICS_DEVICE_MANAGER));
	}
	catch(AE::Exception &exception)
	{
		assert(0 && exception.getMessage().c_str());
	}

	pluginGroupAllegro->install(0);

	AE::OS::Config config(AE::OS::CO_FONT | AE::OS::CO_GEOMETRY | AE::OS::CO_IMAGE);

	AE::Graphics::Device::Driver *deviceDriver = graphicsDeviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_OPENGL);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2(640, 480);
	windowDesc.position = AE::Math::Point2(100, 100);
	//AE::OS::Window *window = AE::OS::WindowManager::getInstance()->createWindow("Drawing Test", windowDesc, AE::Graphics::Device::CO_DX9);
	AE::OS::Window *window = windowManager->createWindow("Drawing Test", windowDesc, deviceDriver);

	MyWindowListener myWindowListener;
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(&myWindowListener);

	AE::Graphics::FontFactory *fontFactory = AE::Graphics::FontFactory::getInstance();
	
	AE::Graphics::FontFace *fontFace;
	try
	{
		fontFace = fontFactory->createFontFace("arial.ttf", 0, 16, 0, 0, AE::Graphics::FO_MONOCHROME);
	}
	catch(AE::Exception &exception)
	{
		if(exception.getType() == AE::ET_FILE_NOT_FOUND)
			fontFace = 0;
	}
	
	AE::Graphics::FontFace *fontFace2;
	try
	{
		fontFace2 = fontFactory->createFontFace("arial.ttf", 0, 16, 0, 0, AE::Graphics::FO_ANTIALIASING);
	}
	catch(AE::Exception &exception)
	{
		if(exception.getType() == AE::ET_FILE_NOT_FOUND)
			fontFace2 = 0;
	}

	AE::Graphics::GeometryFactory *geometryFactory = AE::Graphics::GeometryFactory::getInstance();

	AE::Graphics::Surface *surface = window->getDeviceContext()->createOffscreenSurface(AE::Math::Point2(200, 200), AE::Graphics::SF_X8R8G8B8, true);

	AE::Graphics::Image *gandalf;
	try
	{
		gandalf = AE::Graphics::ImageFactory::getInstance()->createImage("gandalf.jpg", AE::Graphics::AT_PRIMARY_VIDEO);
	}
	catch(AE::Exception &exception)
	{
		if(exception.getType() == AE::ET_FILE_NOT_FOUND)
			gandalf = 0;
	}
	
	/*surface->lock(AE::Graphics::LT_READWRITE);
		for(AE::uint i = 0; i < 200; i++)
			surface->plot(AE::Graphics::Color(255, 255, 255), AE::Math::Point2(i, 50));
	surface->unlock();*/

	AE::Graphics::Surface *backBuffer = window->getDeviceContext()->getBackBuffer();
	AE::Graphics::Color white(255, 255, 255);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color blue(0, 0, 255);
	
	while(myWindowListener.isRunning())
	{
		eventQueue->getNextEvent(0);
		window->getDeviceContext()->beginRendering(white);

		AE::Graphics::GeometryDescRectangle rectangleDesc;
		rectangleDesc.drawingSurface = backBuffer;

		rectangleDesc.positionTopLeft = AE::Math::Point2(10, 10);
		rectangleDesc.positionBottomRight = AE::Math::Point2(50, 50);
		rectangleDesc.borderColor = blue;
		rectangleDesc.borderThickness = 1;
		rectangleDesc.isFilled = false;
		geometryFactory->drawRectangle(rectangleDesc);

		rectangleDesc.positionTopLeft = AE::Math::Point2(60, 10);
		rectangleDesc.positionBottomRight = AE::Math::Point2(100, 50);
		rectangleDesc.borderThickness = 3;
		geometryFactory->drawRectangle(rectangleDesc);

		rectangleDesc.positionTopLeft = AE::Math::Point2(110, 10);
		rectangleDesc.positionBottomRight = AE::Math::Point2(150, 50);
		rectangleDesc.borderThickness = 5;
		geometryFactory->drawRectangle(rectangleDesc);

		rectangleDesc.positionTopLeft = AE::Math::Point2(160, 10);
		rectangleDesc.positionBottomRight = AE::Math::Point2(200, 50);
		rectangleDesc.fillColor = blue;
		rectangleDesc.isFilled = true;
		geometryFactory->drawRectangle(rectangleDesc);

		AE::Graphics::GeometryDescEllipse ellipseDesc;
		ellipseDesc.drawingSurface = backBuffer;

		ellipseDesc.center = AE::Math::Point2(230, 25);
		ellipseDesc.radii = AE::Math::Point2(20, 15);
		ellipseDesc.borderColor = red;
		ellipseDesc.borderThickness = 1;
		ellipseDesc.isFilled = false;
		geometryFactory->drawEllipse(ellipseDesc);

		ellipseDesc.center = AE::Math::Point2(280, 25);
		ellipseDesc.borderThickness = 3;
		geometryFactory->drawEllipse(ellipseDesc);

		ellipseDesc.center = AE::Math::Point2(330, 25);
		ellipseDesc.borderThickness = 5;
		geometryFactory->drawEllipse(ellipseDesc);

		ellipseDesc.center = AE::Math::Point2(380, 25);
		ellipseDesc.fillColor = red;
		ellipseDesc.isFilled = true;
		geometryFactory->drawEllipse(ellipseDesc);

		AE::Graphics::GeometryDescCircle circleDesc;
		circleDesc.drawingSurface = backBuffer;
		circleDesc.center = AE::Math::Point2(430, 25);
		circleDesc.radius = 20;
		circleDesc.isFilled = false;
		circleDesc.borderColor = green;
		circleDesc.borderThickness = 1;		
		geometryFactory->drawCircle(circleDesc);

		circleDesc.center = AE::Math::Point2(480, 25);
		circleDesc.borderThickness = 3;
		geometryFactory->drawCircle(circleDesc);

		circleDesc.center = AE::Math::Point2(530, 25);
		circleDesc.borderThickness = 5;
		geometryFactory->drawCircle(circleDesc);

		circleDesc.center = AE::Math::Point2(580, 25);
		circleDesc.borderThickness = 1;
		circleDesc.isFilled = true;
		circleDesc.fillColor = green;
		geometryFactory->drawCircle(circleDesc);

		AE::Graphics::GeometryDescLine lineDesc;
		lineDesc.drawingSurface = backBuffer;

		lineDesc.positionStart = AE::Math::Point2(10, 60);
		lineDesc.positionEnd = AE::Math::Point2(50, 100);
		lineDesc.color = red;
		lineDesc.thickness = 1;
		geometryFactory->drawLine(lineDesc);

		lineDesc.positionStart = AE::Math::Point2(60, 60);
		lineDesc.positionEnd = AE::Math::Point2(100, 100);
		lineDesc.color = green;
		lineDesc.thickness = 3;
		geometryFactory->drawLine(lineDesc);

		lineDesc.positionStart = AE::Math::Point2(110, 60);
		lineDesc.positionEnd = AE::Math::Point2(150, 100);
		lineDesc.color = blue;
		lineDesc.thickness = 5;
		geometryFactory->drawLine(lineDesc);

		AE::Graphics::GeometryDescArc arcDesc;
		arcDesc.drawingSurface = backBuffer;

		arcDesc.center = AE::Math::Point2(360, 70);
		arcDesc.radius = 25;
		arcDesc.startAngle = 0;
		arcDesc.deltaAngle = 3.14;
		arcDesc.color = red;
		arcDesc.thickness = 1;
		geometryFactory->drawArc(arcDesc);

		arcDesc.center = AE::Math::Point2(420, 70);
		arcDesc.color = green;
		arcDesc.thickness = 3;
		geometryFactory->drawArc(arcDesc);

		arcDesc.center = AE::Math::Point2(480, 70);
		arcDesc.deltaAngle = 2.9;
		arcDesc.color = blue;
		arcDesc.thickness = 15;
		geometryFactory->drawArc(arcDesc);

		AE::Graphics::GeometryDescDonut donutDesc;
		donutDesc.drawingSurface = backBuffer;
		donutDesc.center = AE::Math::Point2(580, 70);
		donutDesc.radii = AE::Math::Point2(25, 50);
		donutDesc.startAngle = 0.5;
		donutDesc.deltaAngle = 3.1415;
		donutDesc.isFilled = true;
		donutDesc.fillColor = green;
		donutDesc.borderThickness = 1;
		donutDesc.borderColor = black;
		donutDesc.borderPosition = AE::Graphics::BP_CENTER;
		geometryFactory->drawDonut(donutDesc);

		AE::Real points[8] = {200, 60, 300, 60, 200, 100, 300, 100};
		AE::Graphics::GeometryDescSpline splineDesc;
		splineDesc.drawingSurface = backBuffer;
		splineDesc.setPoints(points);
		splineDesc.color = black;
		splineDesc.thickness = 1;
		splineDesc.drawAll = false;
		geometryFactory->drawSpline(splineDesc);

		if(fontFace) fontFace->write("Monocromático", AE::Math::Point2(10, 130), black);
		if(fontFace2) fontFace2->write("Com antialiasing", AE::Math::Point2(180, 130), black);

		if(gandalf) backBuffer->blit(gandalf->getSurface(), gandalf->getSurface()->getDimensions(), AE::Math::Point2(100, 160));

		AE::Graphics::GeometryDescPie pieDesc;
		pieDesc.drawingSurface = backBuffer;
		pieDesc.center = AE::Math::Point2(360, 180);
		pieDesc.radii = AE::Math::Point2(0, 50);
		pieDesc.totalSlices = 3;
		pieDesc.numSlices = 3;
		pieDesc.isFilled = true;
		pieDesc.fillColor = green;
		pieDesc.borderThickness = 1;
		pieDesc.borderColor = black;
		pieDesc.borderPosition = AE::Graphics::BP_CENTER;
		geometryFactory->drawPie(pieDesc);

		//backBuffer->clear(AE::Graphics::Color(255, 255, 255));
		// AE::Graphics::LT_WRITE is not working - verify
		//backBuffer->lock(AE::Graphics::LT_WRITE);
		backBuffer->lock(AE::Graphics::LT_READWRITE);
			//backBuffer->clear(AE::Graphics::Color(255, 255, 255));
			//for(AE::uint i = 0; i < 200; i++)
			//	backBuffer->plot(AE::Graphics::Color(255, 0, 0), AE::Math::Point2(i, i+50));
		backBuffer->unlock();

		window->getDeviceContext()->endRendering();
	}

	fontFactory->destroyFontFace(fontFace);
	fontFactory->destroyFontFace(fontFace2);

	//AE::Graphics::ImageFactory::getInstance()->destroyImage(gandalf);

	pluginManager->shutdown();
}