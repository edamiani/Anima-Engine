#include "AnimaTestSuite.h"

#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsCamera2d.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsDeviceFrameBuffer.h"
#include "AnimaGraphicsDeviceManagerGL1_5.h"
#include "AnimaGraphicsDevicePixelBuffer.h"
#include "AnimaGraphicsFontFace.h"
#include "AnimaGraphicsFontFaceDesc.h"
#include "AnimaGraphicsFontFactory.h"
#include "AnimaGraphicsFontManagerFT.h"
#include "AnimaGraphicsImage.h"
#include "AnimaGraphicsImageFactory.h"
#include "AnimaGraphicsImageLoaderPNG.h"
#include "AnimaGraphicsManager.h"
#include "AnimaGraphicsMesh.h"
#include "AnimaGraphicsViewport.h"
#include "AnimaOSWindow.h"
#include "AnimaMathRectangle.h"
#include "AnimaMVCControllerFSM.h"
#include "AnimaMVCControllerFSMState.h"
#include "AnimaMVCModel.h"
#include "AnimaMVCView.h"

#ifdef AE_PLATFORM_WIN32
#	include "AnimaOSWindowManagerWin.h"
#elif defined AE_PLATFORM_LINUX
#	include "AnimaOSWindowManagerLinux.h"
#endif

#include "AnimaPlatform.h"
#include "AnimaPluginManager.h"

#include <list>
#include <utility>

#define USING_OPENGL 0

typedef std::pair<AE::Graphics::VertexBuffer *, AE::Graphics::IndexBuffer *> Object;

enum ControllerFSMState
{
	CS_MAIN
};



class MyModel: public AE::MVC::Model
{
public:
	MyModel(AE::Graphics::Manager *graphicsManager) : mGraphicsManager(graphicsManager) 
	{
#if USING_OPENGL == 0
		mCamera = new AE::Graphics::Camera2d();
#else
		mCamera = new AE::Graphics::Camera2d(true);
#endif
		mCamera->setPosition(AE::Math::Vector3(0, 0, 0));
		mCamera->setWindowDimensions(AE::Math::Vector2(-5, -5), AE::Math::Vector2(5, 5));

		/*mGandalf = AE::Graphics::Manager::getInstance()->getImageFactory()->loadImage("gandalf2_large.png", AE::Graphics::AT_SYSTEM_MEMORY);

		AE::Graphics::Font::Manager *fontManager = AE::Graphics::Manager::getInstance()->getFontManager();
		fontManager->registerFontFile("arial.ttf", "Arial");

		AE::Graphics::Font::FaceDesc fontFaceDesc;
		fontFaceDesc.fontType = AE::Graphics::FT_TRUETYPE;
		fontFaceDesc.glyphDimensions.x = 32;
		fontFaceDesc.glyphDimensions.y = 32;
		fontFaceDesc.horizontalResolution = 72;
		fontFaceDesc.registeredFontName = "Arial";
		fontFaceDesc.verticalResolution = 72;

		mArial32 = fontManager->createFontFace("arial32", fontFaceDesc);*/
	}

	~MyModel() 
	{ 
		std::list<AE::Graphics::IndexBuffer *>::iterator iIB;
		for(iIB = mIBs.begin(); iIB != mIBs.end(); iIB++)
			delete (*iIB);

		std::list<AE::Graphics::VertexBuffer *>::iterator iVB;
		for(iVB = mVBs.begin(); iVB != mVBs.end(); iVB++)
			delete (*iVB);

		mMeshes.clear();
		mObjects.clear();
		mIBs.clear();
		mVBs.clear();
	}

	AE::Graphics::Font::Face*			getArial32() { return mArial32; }
	AE::Graphics::Camera*				getCamera() { return mCamera; }
	AE::Graphics::Image*				getGandalf() { return mGandalf; }
	std::list<AE::Graphics::Mesh *>&	getMeshes() { return mMeshes; }
	std::list<Object>&					getObjects() { return mObjects; }

	void insert(AE::Graphics::Mesh *mesh)
	{
		mMeshes.push_back(mesh);
	}

	void insert(AE::Graphics::VertexBuffer *vb, AE::Graphics::IndexBuffer *ib)
	{
		Object obj;
		obj.first = vb;
		obj.second = ib;

		mVBs.push_back(vb);
		mIBs.push_back(ib);
		mObjects.push_back(obj);
	}

private:
	AE::Graphics::Font::Face *mArial32;
	AE::Graphics::Image *mGandalf;

	AE::Graphics::Manager *mGraphicsManager;
	std::list<AE::Graphics::IndexBuffer *> mIBs;
	std::list<AE::Graphics::Mesh *> mMeshes;
	std::list<AE::Graphics::VertexBuffer *> mVBs;
	std::list<Object> mObjects;
	AE::Graphics::Camera *mCamera;
};



AE::Graphics::Image* scale(AE::Graphics::Image *sourceImage, const AE::Math::Point2<AE::Real> &scalingFactor)
{
	AE::Math::Point2<AE::uint> imageDimensions(sourceImage->getDimensions());
	AE::uint scaledX = (AE::uint)(imageDimensions.x / scalingFactor.x);
	AE::uint scaledY = (AE::uint)(imageDimensions.y / scalingFactor.y);

	AE::uint numPixels = imageDimensions.x;

	AE::Real horizontalRatio = ((AE::Real)(imageDimensions.x - 1)) / (scaledX - 1);
	AE::Real verticalRatio = ((AE::Real)(imageDimensions.y - 1)) / (scaledY - 1);

	AE::Real *horizontalCumulative = (AE::Real *)malloc(scaledX * sizeof(AE::Real));
	horizontalCumulative[0] = 1.0f;

	AE::uint i = 0, j = 0, k = 0;

	// Horizontal scaling
	// Enlargement
	if(horizontalRatio < 1.0f)
	{
	}
	// Reduction
	else
	{
	}

	return 0;
}




class MyView : public AE::MVC::View
{
public:
	MyView(AE::OS::Window *window, MyModel *model) 
		: View(window), mModel(model)
	{
		mViewport = new AE::Graphics::Viewport(static_cast<MyModel *>(mModel)->getCamera());
		AE::Graphics::Manager::getInstance()->setViewport(mViewport);

		AE::Graphics::AxesConvention2d::horizontalDirection = AE::Graphics::HD_LEFT_TO_RIGHT;
		AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_TOP_TO_BOTTOM;
	}

	~MyView() {  }

	void render()
	{
		if(mWindow->getDeviceContext()->beginRendering(AE::Graphics::Color(128, 0, 0, 255)))
		{
			/*std::list<Object> objects = static_cast<MyModel *>(mModel)->getObjects();
			std::list<Object>::iterator i;

			for(i = objects.begin(); i != objects.end(); i++)
				mGraphicsManager->render(AE::Graphics::ROT_TRIANGLE_LIST, (*i).first, (*i).second);
			std::list<AE::Graphics::Mesh *> meshes = static_cast<MyModel *>(mModel)->getMeshes();
			std::list<AE::Graphics::Mesh *>::iterator i;

			AE::Math::Matrix4 identity;
			identity.setIdentity();

			for(i = meshes.begin(); i != meshes.end(); i++)
				mGraphicsManager->render(identity, *i);*/

			AE::Graphics::Device::FrameBuffer *frameBuffer = mWindow->getDeviceContext()->getFrameBuffer();
			AE::Graphics::Image *image = mModel->getGandalf();
			AE::Graphics::Font::Face *arial32 = mModel->getArial32();
			AE::Graphics::Color white(255, 255, 255);

			frameBuffer->lock(AE::Graphics::LT_DISCARD);
				/*frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-100, -100));
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
				frameBuffer->writeFrom(image->getPixelBuffer(), AE::Math::Point2(0, 0), image->getPixelBuffer()->getDimensions(), AE::Math::Point2(-940, 780));*/

			//arial32->print(frameBuffer, L"Go back to the shadow, flame of Udûn!", AE::Math::Point2(80, 350), white);
			arial32->print(frameBuffer, L"Go back to the shadow, flame of Udûn!", AE::Math::Point2<AE::int32>(0, 0), white);
			frameBuffer->unlock();

			mWindow->getDeviceContext()->endRendering();
		}
	}

private:
	MyModel *mModel;
	AE::Graphics::Viewport *mViewport;
};



class MyControllerState : public AE::MVC::ControllerFSMState
{
public:
	MyControllerState(int type, AE::MVC::Controller *parentController, AE::MVC::Model *model, AE::MVC::View *view) :
		ControllerFSMState(type, parentController, model, view) {  }
	~MyControllerState() {}

	void onUpdate(float dt)
	{
		mView->render();
	}
};



class MyController : 
	public AE::MVC::ControllerFSM,
	public AE::OS::KeyListener, 
	public AE::OS::MouseListener, 
	public AE::OS::WindowListener
{
public:
	MyController() : mIsRunning(true)
	{
		mPluginManager = AE::PluginManager::initialize();

		mGraphicsManager = static_cast<AE::Graphics::Manager *>(mPluginManager->registerPlugin("graphicsManager", new AE::Graphics::Manager()));
		mPluginManager->getRoot()->attach(mGraphicsManager);

#ifdef AE_PLATFORM_WIN32
		AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(mPluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerWin()));
#else
		AE::OS::WindowManager *windowManager = static_cast<AE::OS::WindowManager *>(mPluginManager->registerPlugin("windowManager", new AE::OS::WindowManagerLinux()));
#endif	
		AE::Graphics::Manager *graphicsManager = static_cast<AE::Graphics::Manager *>(mPluginManager->registerPlugin("graphicsManager", new AE::Graphics::Manager()));

		mPluginManager->getRoot()->attachAndInstall(windowManager, AE::NO_OPTIONS);
		mPluginManager->getRoot()->attachAndInstall(graphicsManager, AE::Graphics::GMO_GL15 | AE::Graphics::GMO_IMAGE_PNG);

		AE::OS::WindowDesc windowDesc;
		windowDesc.deviceDriverNumber = 0;
		windowDesc.dimensions = AE::Math::Point2<AE::uint>(640, 480);
		windowDesc.fullScreen = false;
		windowDesc.position = AE::Math::Point2<AE::int32>(100, 100);
		windowDesc.setColorFormat(AE::Graphics::CF_R8G8B8A8);
		AE::OS::Window *window = mWindowManager->createWindow("Lila - Prototype", windowDesc, 0);

		mEventQueue = mWindowManager->getEventQueue();
		mEventQueue->registerWindowListener(this);
		mEventQueue->registerKeyListener(this);
		mEventQueue->registerMouseListener(this);

		window->show();

		mModel = new MyModel(mGraphicsManager);

		mView = new MyView(window, mModel);

		MyControllerState *state = new MyControllerState(CS_MAIN, this, mModel, mView);
		this->addState(state);
		this->setDefaultState(state);
		this->execute();
	}

	~MyController()
	{
		mPluginManager->shutdown();

		delete mView;
		delete mModel;
	}

	/***** Inherited from AE::MVC::FrontControllerFSM *****/
	void execute()
	{
		while(mIsRunning)
		{
			updateMachine(0.0f);

			mEventQueue->getNextEvent(0);
		}
	}

	AE::Graphics::Manager* getGraphicsManager()
	{
		return mGraphicsManager;
	}

	/***** Inherited from AE::OS::KeyListener *****/
	void	onKeyDown(const AE::OS::EventKeyboard &event) {}
	void	onKeyTranslation(const AE::OS::EventKeyTranslation &event) {}
	void	onKeyUp(const AE::OS::EventKeyboard &event) {}

	/***** Inherited from AE::OS::MouseListener *****/
	void	onButtonDown(const AE::OS::EventMouse &event) {}
	void	onButtonUp(const AE::OS::EventMouse &event) {}
	void	onMouseMove(const AE::OS::EventMouse &event) {}
	
	/***** Inherited from AE::OS::WindowListener *****/
	void	onClose(AE::OS::Window *window) { mIsRunning = false; }

protected:
	AE::Graphics::Device::Context	*mDeviceContext;
	AE::Graphics::Device::Driver	*mDeviceDriver;
	AE::Graphics::Device::Manager	*mDeviceManager;
	AE::OS::EventQueue				*mEventQueue;
	AE::Graphics::Manager			*mGraphicsManager;
	AE::Graphics::ImageFactory		*mImageFactory;
	AE::Graphics::ImageLoader		*mImageLoader;
	bool							mIsRunning;
	MyModel							*mModel;
	AE::PluginManager				*mPluginManager;
	AE::OS::WindowManager			*mWindowManager;
	MyView							*mView;
};



void ExampleTestSuite::scalingTest()
{
	MyController *controller = new MyController();

	/*AE::Graphics::VertexBufferDesc vbd;
	AE::Math::Vector3 vertexPosition;
	std::vector<AE::Math::Vector3> positions;

	AE::Graphics::RGBA color;

#if defined(AE_PLATFORM_WIN32)
	#if USING_OPENGL == 1
		// OpenGL
		vertexPosition = AE::Math::Vector3(0, 5, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(0, 0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(5, 0, -5.0); positions.push_back(vertexPosition);
		color = 0x000000ff;
	#elif USING_OPENGL == 0
		// DX9
		vertexPosition = AE::Math::Vector3(5, 0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(0, 0, -5.0); positions.push_back(vertexPosition);
		vertexPosition = AE::Math::Vector3(0, 5, -5.0); positions.push_back(vertexPosition);
		color = 0x00ff0000;
	#endif
#else	
	// OpenGL
	vertexPosition = AE::Math::Vector3(0, 5, -5.0); positions.push_back(vertexPosition);
	vertexPosition = AE::Math::Vector3(0, 0, -5.0); positions.push_back(vertexPosition);
	vertexPosition = AE::Math::Vector3(5, 0, -5.0); positions.push_back(vertexPosition);
	color = 0x000000ff;
#endif
	
	vbd.positions = &positions;

	std::vector<AE::Graphics::RGBA> diffuseColors;
	diffuseColors.push_back(color);
	diffuseColors.push_back(color);
	diffuseColors.push_back(color);
	vbd.diffuseColors = &diffuseColors;
	vbd.vertexElements |= AE::Graphics::VE_DIFFUSE;

	vbd.bufferChangeFrequency = AE::Graphics::BCF_STATIC;
	vbd.bufferUsage = AE::Graphics::BU_USER_WRITE;
	AE::Graphics::VertexBuffer *vb = controller->getGraphicsManager()->createVertexBuffer(vbd);
	
	std::vector<AE::ushort> indices;
	indices.push_back(0); indices.push_back(1); indices.push_back(2);
	AE::Graphics::IndexBuffer *ib = controller->getGraphicsManager()->createIndexBuffer(indices, AE::Graphics::BU_USER_READ, AE::Graphics::BCF_STATIC);

	AE::Graphics::Mesh *mesh = controller->getGraphicsManager()->createMesh(AE::Graphics::ROT_TRIANGLE_LIST, vb, ib);

	model->insert(mesh);*/

	controller->execute();

	delete controller;
}