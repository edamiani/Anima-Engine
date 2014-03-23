#include "AnimaGraphicsEnums.h"
#include "AnimaGraphicsFontFactory.h"
#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsImageFactory.h"
#include "AnimaGraphicsImage.h"
#include "AnimaGraphicsGeometryFactory.h"
#include "AnimaGuiButton.h"
#include "AnimaGuiButtonDesc.h"
#include "AnimaGuiContainer.h"
#include "AnimaGuiLayout.h"
#include "AnimaGuiLayoutFactory.h"
#include "AnimaGuiWidgetContentText.h"
#include "AnimaGuiWidgetFactory.h"
#include "AnimaGuiWidgetFactoryComponentButton.h"
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

void ExampleTestSuite::guiTest()
{
	AE::OS::Config config(AE::OS::CO_GUI);

	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2(640, 480);
	windowDesc.position = AE::Math::Point2(100, 100);
	AE::OS::Window *window = AE::OS::WindowManagerAllegro::getInstance()->createWindow("GUI Test", windowDesc, AE::Graphics::Device::CO_DX9);

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

	AE::Gui::WidgetFactory::initialize();

	AE::Gui::WidgetFactory *widgetFactory = AE::Gui::WidgetFactory::getInstance();
	assert(widgetFactory->registerComponent("button", new AE::Gui::WidgetFactoryComponentButton()));

	AE::Math::Point2 layoutDimensions = AE::Math::Point2(window->getDimensions().x, window->getDimensions().y);
	AE::Gui::Layout *guiLayout = AE::Gui::LayoutFactory::getInstance()->createLayout(AE::Math::Point2(0, 0), layoutDimensions);
	AE::Gui::Container *root = guiLayout->getRoot();

	AE::Gui::ButtonDesc buttonDesc;
	buttonDesc.label = new AE::Gui::WidgetContentText(fontFace, "button");
	AE::Gui::Button *button1 = static_cast<AE::Gui::Button *>(widgetFactory->create("button", buttonDesc));
	root->attachWidget(button1, AE::Math::Point2(100, 100));

	/*AE::Gui::Container *container1 = widgetFactory->create("container");
	AE::Gui::Image *image1 = widgetFactory->create("image");
	container1->attachWidget(image1);
	root->attachWidget(container1);
	*/
	
	while(myWindowListener.isRunning())
	{
		eventManager->getNextEvent(0);
		window->getDeviceContext()->beginRendering(white);

		guiLayout->render();

		window->getDeviceContext()->endRendering();
	}

	AE::Gui::WidgetFactory::shutdown();

	fontFactory->destroyFontFace(fontFace);
}