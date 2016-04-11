#include "AnimaTestSuite.h"

#include "Anima/Exception.h"
#include "Anima/Graphics/Device/Context.h"
#include "Anima/Graphics/Device/Driver.h"
#include "Anima/Graphics/Device/FrameBuffer.h"
#include "Anima/Graphics/Device/GL15/ManagerGL15.h"
#include "Anima/Graphics/Device/PixelBuffer.h"
#include "Anima/Graphics/Device/VertexBuffer.h"
#include "Anima/Math/Math.h"
#include "Anima/Math/Point2.h"
#include "Anima/OS/WindowListener.h"

#ifdef AE_PLATFORM_WIN32
#	include "Anima/OS/Win/WindowManagerWin.h"
#elif defined AE_PLATFORM_LINUX
#	include "Anima/OS/Linux/WindowManagerLinux.h"
#endif

#include "Anima/PluginManager.h"

#include <cassert>
#include <climits>
#include <cmath>
#include <list>
#include <map>
#include <vector>

AE::Graphics::Device::VertexBuffer* createCube(AE::Graphics::Device::Driver *deviceDriver, float size, const AE::Graphics::Color &color)
{
	AE::Graphics::Device::VertexBuffer *cubeVB = deviceDriver->createEmptyVertexBuffer(AE::Graphics::VE_POSITION | AE::Graphics::VE_DIFFUSE | AE::Graphics::VE_NORMAL, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STREAM);

	cubeVB->lock();
	{
		// Top
		cubeVB->addPosition(AE::Math::Vector3(size / 2, size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(size / 2, size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);

		// Bottom
		cubeVB->addPosition(AE::Math::Vector3(size / 2, -size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, -1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, -size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, -1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, -size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, -1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(size / 2, -size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, -1, 0));
		cubeVB->addDiffuseColor(color);

		// Front
		cubeVB->addPosition(AE::Math::Vector3(size / 2, size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, -size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(size / 2, -size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);

		// Back
		cubeVB->addPosition(AE::Math::Vector3(size / 2, size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, -size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(size / 2, -size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);

		// Left
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, -size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(-size / 2, -size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);

		// Right
		cubeVB->addPosition(AE::Math::Vector3(size / 2, size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(size / 2, size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(size / 2, -size / 2, size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
		cubeVB->addPosition(AE::Math::Vector3(size / 2, -size / 2, -size / 2));
		cubeVB->addNormal(AE::Math::Vector3(0, 1, 0));
		cubeVB->addDiffuseColor(color);
	}
	cubeVB->unlock();

	return cubeVB;
}

class Test3DListener : public AE::OS::WindowListener, AE::OS::KeyListener
{
public:
	Test3DListener() : mIsRunning(true) {}
	~Test3DListener() {}

	bool isRunning() { return mIsRunning; }

	void onClose(AE::OS::Window *window)
	{
		mIsRunning = false;
	}

protected:
	bool mIsRunning;
};

void ExampleTestSuite::test3D()
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
	AE::OS::Window *window = windowManager->createWindow("3D Test", windowDesc);

	Test3DListener myWindowListener;
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

	//GLfloat colors[] = { 1, 1, 1,   1, 1, 0,   1, 0, 0, };

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

	AE::Graphics::Device::VertexBuffer *circleVB = deviceDriver->createEmptyVertexBuffer(AE::Graphics::VE_POSITION | AE::Graphics::VE_DIFFUSE, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STREAM);
	AE::Graphics::Device::VertexBuffer *parabolaVB = deviceDriver->createEmptyVertexBuffer(AE::Graphics::VE_POSITION | AE::Graphics::VE_DIFFUSE, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STREAM);
	AE::Graphics::Device::VertexBuffer *triangleVB = deviceDriver->createEmptyVertexBuffer(AE::Graphics::VE_POSITION | AE::Graphics::VE_DIFFUSE, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STREAM);
	
	circleVB->lock();
	{
		int numOfSides = 128;
		float center = 100.0f;
		float radius = 100.0f;

		//glColor3f(1, 0, 0);

		for(int i = 0; i < numOfSides; i++)
		{
			float radian = (AE::Math::PI * 10.0f) * (i / (float)numOfSides);
			AE::Math::Vector3 v(radius * cos(radian) + center + (i * 3), radius * sin(radian) + center, 0);
			circleVB->addPosition(v);
			circleVB->addDiffuseColor(AE::Graphics::Color(255, 0, 0));
		}
	}
	circleVB->unlock();

	parabolaVB->lock();
	{
		int numOfSteps = 32;
		float center = 200.0f;
		float radiusX = 100.0f;
		float radiusY = 200.0f;

		//glColor3f(0, 1, 0);

		for(int i = 0; i < numOfSteps; i++)
		{
			float radian = (2 * (i / ((float)numOfSteps - 1))) - 1;
			AE::Math::Vector3 v((radiusX * radian) + center, radiusY * (radian * radian) + center, 0);
			parabolaVB->addPosition(v);
			parabolaVB->addDiffuseColor(AE::Graphics::Color((int)((i / (float)numOfSteps) * 255), 255, (int)(((numOfSteps - i) / (float)numOfSteps) * 255)));
		}
	}
	parabolaVB->unlock();

	triangleVB->lock();
	{
		triangleVB->addPosition(AE::Math::Vector3(500, 300, 0));
		triangleVB->addDiffuseColor(AE::Graphics::Color(255, 0, 0));
		triangleVB->addPosition(AE::Math::Vector3(500, 400, 0));
		triangleVB->addDiffuseColor(AE::Graphics::Color(0, 255, 0));
		triangleVB->addPosition(AE::Math::Vector3(400, 400, 0));
		triangleVB->addDiffuseColor(AE::Graphics::Color(0, 0, 255));
	}
	triangleVB->unlock();

	// Polygon test
	std::vector<AE::Math::Vector3>	positions;
	positions.push_back(AE::Math::Vector3(300, 100, 0));
	positions.push_back(AE::Math::Vector3(300, 300, 0));
	positions.push_back(AE::Math::Vector3(100, 100, 0));

	std::vector<AE::Math::Vector3>	colors;
	colors.push_back(AE::Math::Vector3(1, 0, 0));
	colors.push_back(AE::Math::Vector3(0, 0, 1));
	colors.push_back(AE::Math::Vector3(0, 1, 0));

	AE::uint id;
	glGenBuffers(1, (GLuint *)&id);

	size_t positionsSize = sizeof(AE::Math::Vector3) * positions.size();
	size_t colorsSize = sizeof(AE::Math::Vector3) * colors.size();

	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, positionsSize + colorsSize, 0, GL_STREAM_READ);

	glBufferSubData(GL_ARRAY_BUFFER, 0, positionsSize, positions.data());
	glBufferSubData(GL_ARRAY_BUFFER, positionsSize, colorsSize, colors.data());

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// End of polygon test

	while(myWindowListener.isRunning())
	{
		deviceContext->beginRendering(black);

		AE::Graphics::Device::FrameBuffer *frameBuffer = deviceContext->getFrameBuffer();
		frameBuffer->lock(AE::Graphics::LT_DISCARD);
		//frameBuffer->clear(red);

		frameBuffer->plot(green.getRGBA(), AE::Math::Point2<AE::int32>(100, 100));

		/*glBindBuffer(GL_ARRAY_BUFFER, buffers[VERTICES]);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[INDICES]);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, BUFFER_OFFSET(0));*/

		//glDrawElements(GL_QUADS, 1, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_BYTE, 0);

		/*glDisableClientState(GL_VERTEX_ARRAY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/

		deviceContext->draw3dObject(AE::Graphics::ROT_LINE_STRIP, circleVB);
		deviceContext->draw3dObject(AE::Graphics::ROT_LINE_STRIP, parabolaVB);
		deviceContext->draw3dObject(AE::Graphics::ROT_TRIANGLE_LIST, triangleVB);		

		// Polygon test
		glBindBuffer(GL_ARRAY_BUFFER, id);

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, 0);
		glColorPointer(3, GL_FLOAT, 0, (void *)positionsSize);

		//glDrawArrays(GL_LINE_LOOP, 0, positions.size());

		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// End of polygon test

		glBegin(GL_POLYGON);
		glVertex3f(20, 20, 0);
		glVertex3f(80, 20, 0);
		glVertex3f(80, 80, 0);
		glVertex3f(20, 80, 0);
		glEnd();

		frameBuffer->unlock();

		deviceContext->endRendering();

		eventQueue->getNextEvent(0);
	}

	pluginManager->shutdown();
}
