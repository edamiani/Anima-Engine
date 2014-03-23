#include "AnimaGraphicsDeviceManager.h"
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

void ExampleTestSuite::gpuTest()
{
	AE::OS::Config config(AE::OS::CO_GUI);
	AE::OS::WindowDesc windowDesc;
	windowDesc.dimensions = AE::Math::Point2(640, 480);
	windowDesc.position = AE::Math::Point2(100, 100);
	AE::OS::Window *window = AE::OS::WindowManagerAllegro::getInstance()->createWindow("GPU Test", windowDesc, AE::Graphics::Device::CO_OPENGL);

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

	//AE::Graphics::Device *graphicsDevice1 = static_cast<AE::Graphics::Device *>(AE::OS::DeviceManager::getInstance()->acquireDevice(AE::OS::DT_GRAPHICS_PRIMARY, 0));
		
	/*AE::Graphics::Device::Driver *deviceDriver = graphicsDevice1->acquireDriver(AE::Graphics::DT_OPENGL);

	AE::Graphics::VertexFormat vertexFormat;
	vertexFormat.add(AE::Graphics::VF_XYZ);

	AE::Graphics::VertexBuffer *vertexBuffer = deviceDriver->createVertexBuffer(vertexFormat, 4, AE::Graphics::BU_NONE);
	vertexBuffer->lock();
		AE::Graphics::Vertex v(vertexFormat);
		//vertexBuffer->insert(v << -1.0 << -1.0 << 0.0)->insert(v << -1.0 <<  1.0 << 0.0)->insert(v <<  1.0 <<  1.0 << 0.0)->insert(v <<  1.0 << -1.0 << 0.0);

		vertexBuffer << (v << -1.0 << -1.0 << 0.0) 
			<< (v << -1.0 <<  1.0 << 0.0)
			<< (v <<  1.0 <<  1.0 << 0.0)
			<< (v <<  1.0 << -1.0 << 0.0)
	vertexBuffer->unlock();

	AE::Graphics::IndexBuffer *indexBuffer = deviceDriver->createIndexBuffer(6, AE::Graphics::BU_NONE);
	indexBuffer->lock();
		//indexBuffer->insert(0)->insert(1)->insert(2)->insert(3)->insert(0)->insert(2);

		indexBuffer << 0 << 1 << 2 << 3 << 0 << 2;
	indexBuffer->unlock();

	deviceDriver->beginRendering();
		deviceDriver->clear(AE::Graphics::Color(0, 0, 0));
		deviceDriver->drawIndexed(vertexBuffer, indexBuffer, AE::Graphics::ROT_TRIANGLE_LIST);
	deviceDriver->endRendering();
	*/
	
	while(myWindowListener.isRunning())
	{
		eventManager->getNextEvent(0);
		window->getDeviceContext()->beginRendering(white);

		//guiLayout->render();

		window->getDeviceContext()->endRendering();
	}

	AE::Gui::WidgetFactory::shutdown();

	fontFactory->destroyFontFace(fontFace);
}