#include "AnimaTestSuite.h"

#include "Anima/AnimaException.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceContext.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceDriver.h"
#include "Anima/Graphics/Device/AnimaGraphicsDeviceFrameBuffer.h"
#include "Anima/Graphics/Device/GL15/AnimaGraphicsDeviceManagerGL15.h"
#include "Anima/Graphics/Device/AnimaGraphicsDevicePixelBuffer.h"
#include "Anima/Math/AnimaMathPoint2.h"
#include "Anima/OS/AnimaOSWindowListener.h"

#ifdef AE_PLATFORM_WIN32
#	include "Anima/OS/Win/AnimaOSWindowManagerWin.h"
#elif defined AE_PLATFORM_LINUX
#	include "Anima/OS/AnimaOSWindowManagerLinux.h"
#endif

#include "Anima/AnimaPluginManager.h"

#include <cassert>
#include <climits>
#include <cmath>
#include <list>
#include <map>
#include <vector>

class MyWindowListener : public AE::OS::WindowListener, AE::OS::KeyListener
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

void ExampleTestSuite::Test3D()
{
	/*AE::PluginManager *pluginManager = AE::PluginManager::getInstance();

	pluginManager->initialize(AE::PT_WINDOW_MANAGER | AE::PT_EVENT_MANAGER | AE::PT_GRAPHICS_MANAGER | AE::PT_SCENE_MANAGER);

	AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(pluginManager->getPlugin(AE::PT_WINDOW_MANAGER));
	AE::OS::EventManager *eventManager = static_cast<AE::OS::EventManager *>(pluginManager->getPlugin(AE::PT_EVENT_MANAGER));
	AE::Graphics::Manager *graphicsManager = static_cast<AE::Graphics::Manager *>(pluginManager->getPlugin(AE::PT_GRAPHICS_MANAGER));
	AE::Scene::Manager *sceneManager = static_cast<AE::Scene::Manager *>(pluginManager->getPlugin(AE::PT_SCENE_MANAGER));

	AE::Graphics::Device *graphicsDevice = graphicsManager->getDevices()[0];

	AE::Math::Vector2 windowDimensions(800, 600);
	AE::OS::Window *window = windowManager->createWindow(windowDimensions);

	AE::Graphics::Viewport *viewport = window->createViewport(windowDimensions.y, 0, 0, windowDimensions.x);

	eventManager->registerWindowEventType(window, AE::OS::ET_WINDOW, MyWindowListener);
	eventManager->registerWindowEventType(window, AE::OS::ET_KEYBOARD, MyWindowListener);

	AE::Graphics::Mesh *cube = AE::Graphics::Util::createBasicMesh(AE::Graphics::Util::BM_CUBE);

	AE::Scene::Instance *scene = sceneManager->createScene();

	AE::Math::Vector3 cubePosition(0, 0, 5);
	AE::Math::Quaternion cubeOrientation(AE::Math::Quaternion::Identity);
	scene->getRoot()->createNode(cube, cubePosition, cubeOrientation);

	AE::Scene::Camera *camera = scene->getActiveCamera();
	camera->setCameraPosition(AE::Math::Vector3(0, 0, 0));
	camera->lookAt(AE::Math::Vector3(0, 0, 1));

	while(mIsRunning)
	{
		graphicsDevice->beginRendering(AE::Color::Black);

		viewport->render(scene);

		graphicsDevice->endRendering();
	}*/





























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
	AE::OS::Window *window = windowManager->createWindow("Plot Test", windowDesc);

	MyWindowListener myWindowListener;
	AE::OS::EventQueue *eventQueue = windowManager->getEventQueue();
	eventQueue->registerWindowListener(&myWindowListener);

	AE::Graphics::Device::Manager *deviceManager;
	AE::Graphics::Device::Driver *deviceDriver;

#ifdef AE_PLATFORM_WIN32
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	deviceManager->install(0);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_GL_15);
#else
	deviceManager = static_cast<AE::Graphics::Device::Manager *>(pluginManager->registerPlugin("deviceManagerGL15", new AE::Graphics::Device::ManagerGL15()));
	deviceManager->install(0);
	deviceDriver = deviceManager->acquireDeviceDriver(0, AE::Graphics::Device::DT_OPENGL1_5);
#endif

	AE::Graphics::Device::ContextDesc contextDesc;
	contextDesc.dimensions = window->getDimensions();
	contextDesc.fullScreen = false;
	contextDesc.parentWindow = window;
	contextDesc.setColorFormat(AE::Graphics::CF_R8G8B8A8);

	AE::Graphics::Device::Context *deviceContext = deviceDriver->createDeviceContext(contextDesc);

	window->show();

	AE::Graphics::Color red(255, 0, 0);
	AE::Graphics::Color green(0, 255, 0);
	AE::Graphics::Color blue(0, 0, 255);
	AE::Graphics::Color black(0, 0, 0);
	AE::Graphics::Color white(255, 255, 255);

#define VERTICES 0 
#define INDICES 1 
#define NUM_BUFFERS 2

#define BUFFER_OFFSET(i) ((void*)(i))

	GLuint buffers[NUM_BUFFERS];
	/*GLfloat vertices[][3] =
	{
	{ -1.0, -1.0, -1.0 },
	{ 1.0, -1.0, -1.0 },
	{ 1.0, 1.0, -1.0 },
	{ -1.0, 1.0, -1.0 },
	{ -1.0, -1.0, 1.0 },
	{ 1.0, -1.0, 1.0 },
	{ 1.0, 1.0, 1.0},
	{ -1.0, 1.0, 1.0 },
	};*/
	GLfloat vertices[][3] =
	{
		{ 100.0, 100.0, 0.0 },
		{ 100.0, 200.0, 0.0 },
		{ 0.0, 200.0, 0.0 },
		{ 0.0, 100.0, 0.0}
	};

	/*GLubyte indices[][4] =
	{
	{ 0, 1, 2, 3 },
	{ 4, 7, 6, 5 },
	{ 0, 4, 5, 1 },
	{ 3, 2, 6, 7 },
	{ 0, 3, 7, 4 },
	{ 1, 5, 6, 2 }
	};*/

	GLubyte indices[] =
	{
		0, 1, 2, 2, 3, 0
	};

	GLfloat colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0, };

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glGenBuffers(NUM_BUFFERS, buffers);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while(myWindowListener.isRunning())
	{
		deviceContext->beginRendering(black);

		AE::Graphics::Device::FrameBuffer *frameBuffer = deviceContext->getFrameBuffer();
		frameBuffer->lock(AE::Graphics::LT_DISCARD);
		//frameBuffer->clear(red);

		frameBuffer->plot(green.getRGBA(), AE::Math::Point2<AE::int32>(100, 100));
		drawLine(frameBuffer, white, AE::Math::Point2<AE::int32>(50, 50), AE::Math::Point2<AE::int32>(100, 50));
		drawLine(frameBuffer, red, AE::Math::Point2<AE::int32>(101, 51), AE::Math::Point2<AE::int32>(150, 100));
		drawLine(frameBuffer, blue, AE::Math::Point2<AE::int32>(151, 101), AE::Math::Point2<AE::int32>(250, 50));
		
		//glBegin(GL_POLYGON);            // These vertices form a closed polygon
		//glColor3f(1.0f, 1.0f, 0.0f); // Yellow
		//glVertex2f(300.f, 100.f);
		//glVertex2f(300.f, 300.f);
		//glVertex2f(100, 100);
		//glEnd();

		glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));

		//glDrawElements(GL_QUADS, 1, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);

		glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		//std::vector<AE::Math::Point2<AE::int32>> points;
		//points.push_back(AE::Math::Point2<AE::int32>(400, 200));
		//points.push_back(AE::Math::Point2<AE::int32>(403, 200));
		//points.push_back(AE::Math::Point2<AE::int32>(406, 203));
		//points.push_back(AE::Math::Point2<AE::int32>(403, 206));
		//points.push_back(AE::Math::Point2<AE::int32>(400, 206));
		//points.push_back(AE::Math::Point2<AE::int32>(397, 203));
		//drawPolygon(frameBuffer, white, points);

		//std::vector<AE::Math::Point2<AE::int32>> points2;
		///*points2.push_back(AE::Math::Point2(2, 3));
		//points2.push_back(AE::Math::Point2(7, 1));
		//points2.push_back(AE::Math::Point2(13, 5));
		//points2.push_back(AE::Math::Point2(13, 11));
		//points2.push_back(AE::Math::Point2(7, 7));
		//points2.push_back(AE::Math::Point2(2, 9));*/
		///*points2.push_back(AE::Math::Point2(50, 50));
		//points2.push_back(AE::Math::Point2(30, 30));
		//points2.push_back(AE::Math::Point2(70, 30));*/
		//points2.push_back(AE::Math::Point2<AE::int32>(200, 200));
		//points2.push_back(AE::Math::Point2<AE::int32>(300, 200));
		//points2.push_back(AE::Math::Point2<AE::int32>(350, 275));
		//points2.push_back(AE::Math::Point2<AE::int32>(300, 350));
		//points2.push_back(AE::Math::Point2<AE::int32>(200, 350));
		//points2.push_back(AE::Math::Point2<AE::int32>(150, 275));
		//drawFilledPolygon(frameBuffer, white, points2);

		//drawCircle(frameBuffer, blue, AE::Math::Point2<AE::int32>(320, 240), AE::int32(5) );
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(10));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(15));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(20));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(25));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(30));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(35));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(40));
		//drawCircle(frameBuffer, red, AE::Math::Point2<AE::int32>(320, 240), AE::int32(45));
		//drawCircle(frameBuffer, blue, AE::Math::Point2<AE::int32>(320, 240), AE::int32(50));

		frameBuffer->unlock();

		deviceContext->endRendering();

		eventQueue->getNextEvent(0);
	}

	pluginManager->shutdown();
}
