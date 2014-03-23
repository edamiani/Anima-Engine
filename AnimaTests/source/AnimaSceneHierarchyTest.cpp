#include "AnimaTestSuite.h"

#include "AnimaException.h"
#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsDeviceContext.h"
#include "AnimaGraphicsDeviceDriver.h"
#include "AnimaGraphicsDeviceManagerGL1_5.h"
#include "AnimaGraphicsDeviceFrameBuffer.h"
#include "AnimaGraphicsDeviceIndexBuffer.h"
#include "AnimaGraphicsDevicePipeline.h"
#include "AnimaGraphicsDevicePixelBuffer.h"
#include "AnimaGraphicsDevicePixelBufferFactory.h"
#include "AnimaGraphicsDeviceSubpipeline2d.h"
#include "AnimaGraphicsDeviceVertexBuffer.h"
#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsFontFaceDesc.h"
#include "AnimaGraphicsFontFactory.h"
#include "AnimaGraphicsFontManagerFT.h"
#include "AnimaGraphicsManager.h"
#include "AnimaGraphicsImage.h"
#include "AnimaGraphicsImageFactory.h"
#include "AnimaGraphicsImageManager.h"
#include "AnimaMathMatrix4.h"
#include "AnimaMathPoint2.h"
#include "AnimaMathRectangle.h"
#include "AnimaMathVector4.h"
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

void ExampleTestSuite::sceneHierarchyTest()
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
			AE::Graphics::GMO_GL15 | AE::Graphics::GMO_IMAGE_PNG | AE::Graphics::GMO_FONT_FT
		)
	);

	AE::OS::WindowDesc windowDesc;
	windowDesc.deviceDriverNumber = 0;
	windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
	windowDesc.fullScreen = false;
	windowDesc.position = AE::Math::Point2<AE::int32>(100, 100);
	windowDesc.setColorFormat(AE::Graphics::CF_R8G8B8A8);
	AE::OS::Window *window = windowManager->createWindow("Scene Hierarchy Test", windowDesc, 0);
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

	AE::Graphics::Font::Manager *fontManager = graphicsManager->getFontManager();
	fontManager->getFontFactory()->registerFontFile("arial.ttf", "Arial");

	AE::Graphics::Font::FaceDesc fontFaceDesc;
	fontFaceDesc.fontOptions = AE::Graphics::FO_MONOCHROME;
	fontFaceDesc.fontType = AE::Graphics::FT_TRUETYPE;
	fontFaceDesc.glyphDimensions.x = 32;
	fontFaceDesc.glyphDimensions.y = 32;
	fontFaceDesc.horizontalResolution = 72;
	fontFaceDesc.registeredFontName = "Arial";
	fontFaceDesc.verticalResolution = 72;

	AE::Graphics::Font::Face *arial32 = fontManager->createFontFace("arial32", fontFaceDesc);

	AE::Graphics::Device::PixelBufferDesc pixelBufferDesc;
	pixelBufferDesc.colorBufferDesc = gandalf->getDesc().colorBufferDesc;
	pixelBufferDesc.colorFormatConversion = frameBuffer->getColorFormat();

	AE::Graphics::Device::PixelBuffer *pbGandalf = deviceManager->getPixelBufferFactory()->createPixelBuffer(pixelBufferDesc);

	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color white(255, 255, 255);

	//AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_BOTTOM_TO_TOP;
	AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_TOP_TO_BOTTOM;

	AE::Math::Matrix4 modelParent(
		1,   0,   0,   0,
		0,   1,   0,   0,
		0,   0,   1,   0,
		50,  10,   0,   1);

	AE::Math::Matrix4 modelChild(
		1,   0,   0,   0,
		0,   1,   0,   0,
		0,   0,   1,   0,
		10,  10,  0,   1);

	AE::Math::Matrix4 view(
		1,   0,   0,   0,
		0,   1,   0,   0,
		0,   0,   1,   0,
		40,  0,   0,   1);

	AE::Math::Matrix4 modelChild2(
		1,   0,   0,   0,
		0,   1,   0,   0,
		0,   0,   1,   0,
		100,  0,  0,   1);

	AE::Math::Matrix4 modelView;



	int direction = 1;

	while(myWindowListener.isRunning())
	{
		AE::Graphics::Device::Subpipeline2d *pipeline2d = static_cast<AE::Graphics::Device::Subpipeline2d *>(
			deviceContext->getPipeline()->getSubpipeline(AE::Graphics::Device::SPLT_2D_OPERATIONS)
		);

		deviceContext->beginRendering(green);

		modelParent[3][0] = modelParent[3][0] + direction;

		if(modelParent[3][0] == 640)
			direction = -1;
		else if(modelParent[3][0] == 0)
			direction = 1;
		
		pipeline2d->setViewMatrix(view);			// Sets a new view matrix and recalculates the model-view matrix
		pipeline2d->setModelMatrix(modelParent);	// Sets a new model matrix and recalculates the model-view matrix
		pipeline2d->enqueueColorBuffer(pbGandalf);	// Enqueues for drawing, but waits for a flush
		pipeline2d->flush();						// Sends everything to the rasterizer and empties the queue
		pipeline2d->pushModelViewMatrix();			// Saves the current model-view matrix
		pipeline2d->composeModelMatrix(modelChild);	// Sets a new model matrix and recalculates the model-view matrix
		pipeline2d->drawColorBuffer(pbGandalf);		// The same as enqueueColorBuffer() followed by flush()
		pipeline2d->popModelViewMatrix();			// Restores the previous model-view matrix
		pipeline2d->composeModelMatrix(modelChild2);// Sets a new model matrix and recalculates the model-view matrix
		pipeline2d->drawColorBuffer(pbGandalf);		// The same as enqueueColorBuffer() followed by flush()

		arial32->print(frameBuffer, L"testg", AE::Math::Point2<AE::int32>(400, 400), AE::Graphics::Color(0, 0, 0));

		deviceContext->endRendering();
		

		/*deviceContext->beginRendering(green);

		frameBuffer->lock(AE::Graphics::LT_DISCARD);

		modelView.setIdentity();
		modelView = view.inverse().multiply(modelParent);
		AE::Math::Point2<AE::int32> position(static_cast<AE::int32>(modelView[3][0]), static_cast<AE::int32>(modelView[3][1]));
		frameBuffer->blitFrom(pbGandalf, AE::Math::Point2<AE::uint>(0, 0), AE::Math::Point2<AE::uint>(pbGandalf->getDimensions().x, pbGandalf->getDimensions().y), AE::Math::Point2<AE::int32>(position.x, position.y));
		
		modelView = modelView.multiply(modelChild);
		position = AE::Math::Point2<AE::int32>(static_cast<AE::int32>(modelView[3][0]), static_cast<AE::int32>(modelView[3][1]));
		frameBuffer->blitFrom(pbGandalf, AE::Math::Point2<AE::uint>(0, 0), AE::Math::Point2<AE::uint>(pbGandalf->getDimensions().x, pbGandalf->getDimensions().y), AE::Math::Point2<AE::int32>(position.x, position.y));

		frameBuffer->unlock();

		deviceContext->endRendering();*/

		eventQueue->getNextEvent(0);
	}

	deviceManager->getPixelBufferFactory()->destroyPixelBuffer(pbGandalf);

	fontManager->destroyFontFace("arial32");

	AE::PluginManager::shutdown();
}
