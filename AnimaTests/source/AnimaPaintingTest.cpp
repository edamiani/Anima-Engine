#include "AnimaTestSuite.h"

#include "AnimaGraphicsAxesConvention2d.h"
#include "AnimaGraphicsCamera2d.h"
#include "AnimaGraphicsColor.h"
#include "AnimaGraphicsDeviceManagerGL15.h"
#include "AnimaGraphicsDevicePixelBufferGL15.h"
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



class MyPaintingModel: public AE::MVC::Model
{
public:
	MyPaintingModel(AE::Graphics::Manager *graphicsManager) : mGraphicsManager(graphicsManager) 
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

		mArial32 = fontManager->createFontFace("arial32", fontFaceDesc);


		// OpenGL stub
		glGenTextures(1, &mTexture);

		//int xSize = 256, ySize = 256; //size of texture
		int xSize = 1024, ySize = 512; //size of texture
		//new array
		unsigned char *colorBits = new unsigned char[ xSize * ySize * 3 ];
		memset(colorBits, 0xFF, 1024 * 512 * 3);

		//texture creation..
		//glGenTextures(1,&texture);
		GLenum error;
		glBindTexture(GL_TEXTURE_2D, mTexture);
		error = glGetError();

		//unsigned char *colorBits = (unsigned char *)(mGandalf->getSurface()->getData());
		glTexImage2D(GL_TEXTURE_2D, 0, 3, xSize, ySize, 0, GL_RGB, GL_UNSIGNED_BYTE, colorBits);
		error = glGetError();
		
		GLint format;
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);

		//you can set other texture parameters if you want
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		delete[] colorBits;

		GLubyte pixel[3];
		pixel[0] = 0;
		pixel[1] = 0;
		pixel[2] = 0;
		//pixel[3] = 255;
		glTexSubImage2D(GL_TEXTURE_2D, 0, 100, 100, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
		error = glGetError();

		AE::Graphics::Device::PixelBufferDesc pbd;
		pbd.colorFormat = AE::Graphics::Device::CF_R8G8B8X8;
		pbd.dimensions = AE::Math::Point2(100, 100);
		pbd.usage = AE::Graphics::Device::BU_DYNAMIC_WRITE;

		AE::Graphics::Device::PixelBuffer *pb = new AE::Graphics::Device::PixelBufferGL1_5(pbd);*/
	}

	~MyPaintingModel() 
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
	GLuint								getGLTexture() { return mTexture; }
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

	// Stub
	GLuint mTexture;
};



class MyPaintingView : public AE::MVC::View
{
public:
	MyPaintingView(AE::OS::Window *window, MyPaintingModel *model) 
		: View(window), mModel(model)
	{
		mViewport = new AE::Graphics::Viewport(static_cast<MyPaintingModel *>(mModel)->getCamera());
		AE::Graphics::Manager::getInstance()->setViewport(mViewport);

		AE::Graphics::AxesConvention2d::horizontalDirection = AE::Graphics::HD_LEFT_TO_RIGHT;
		AE::Graphics::AxesConvention2d::verticalDirection = AE::Graphics::VD_TOP_TO_BOTTOM;
	}

	~MyPaintingView() {  }

	void render()
	{
		if(mWindow->getDeviceContext()->beginRendering(AE::Graphics::Color(128, 0, 0, 255)))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
			glLoadIdentity();									// Reset The Modelview Matrix
			glBindTexture(GL_TEXTURE_2D, mModel->getGLTexture());	// Select Our Texture
			
			glDisable(GL_BLEND);								// Disable Blending Before We Draw In 3D
			glColor3f(1.0f,1.0f,0.0f);							// Bright White
			
			glDisable(GL_DEPTH_TEST);							// Disables Depth Testing
			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glPushMatrix();										// Store The Projection Matrix
			glLoadIdentity();									// Reset The Projection Matrix
			glOrtho(0,640,0,480,-1,1);							// Set Up An Ortho Screen

			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glPushMatrix();										// Store The Modelview Matrix
			glLoadIdentity();									// Reset The Modelview Matrix

			glBegin(GL_QUADS);									// Draw My Texture Mapped Quad
				glTexCoord2d(0.0f,0.0f);						// First Texture Coord
				glVertex2f(0, 0);								// First Vertex
				glTexCoord2d(0.0f,1.0f);						// Second Texture Coord
				glVertex2f(0, 512);								// Second Vertex
				glTexCoord2d(1.0f,1.0f);						// Third Texture Coord
				glVertex2f(1024, 512);								// Third Vertex
				glTexCoord2d(1.0f,0.0f);						// Fourth Texture Coord
				glVertex2f(1024, 0);								// Fourth Vertex
			glEnd();

			glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
			glPopMatrix();										// Restore The Old Projection Matrix
			glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
			glPopMatrix();										// Restore The Old Projection Matrix
			glEnable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);									// Enable Blending

			glLoadIdentity();									// Reset The View
		}
		mWindow->getDeviceContext()->endRendering();

		/*if(mWindow->getDeviceContext()->beginRendering(AE::Graphics::Color(128, 0, 0, 255)))
		{
			AE::Graphics::Surface *frameBuffer = mWindow->getDeviceContext()->getFrameBuffer();
			AE::Graphics::Image *image = mModel->getGandalf();
			AE::Graphics::Font::Face *arial32 = mModel->getArial32();
			AE::Graphics::Color white(255, 255, 255);

			frameBuffer->lock(AE::Graphics::LT_DISCARD);
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-100, -100));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(220, -100));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(540, -100));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-100, 140));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(220, 140));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(540, 140));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-100, 380));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(220, 380));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(540, 380));

			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-300, -300));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(220, -300));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(940, -300));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-300, 140));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-940, 140));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-300, 780));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(220, 780));
			frameBuffer->blit(image->getSurface(), image->getSurface()->getDimensions(), AE::Math::Point2(-940, 780));

			arial32->print(frameBuffer, L"Go back to the shadow, flame of Udûn!", AE::Math::Point2(0, 0), white);
			frameBuffer->unlock();

			mWindow->getDeviceContext()->endRendering();
		}*/
	}

private:
	MyPaintingModel *mModel;
	AE::Graphics::Viewport *mViewport;
};



class MyPaintingControllerState : public AE::MVC::ControllerFSMState
{
public:
	MyPaintingControllerState(int type, AE::MVC::Controller *parentController, AE::MVC::Model *model, AE::MVC::View *view) :
		ControllerFSMState(type, parentController, model, view) {  }
	~MyPaintingControllerState() {}

	void onUpdate(float dt)
	{
		mView->render();
	}
};



class MyPaintingController : 
	public AE::MVC::ControllerFSM,
	public AE::OS::KeyListener, 
	public AE::OS::MouseListener, 
	public AE::OS::WindowListener
{
public:
	MyPaintingController() : mIsRunning(true)
	{
		mPluginManager = AE::PluginManager::initialize();

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
		AE::OS::Window *window = mWindowManager->createWindow("Painting Test", windowDesc, 0);

		mEventQueue = mWindowManager->getEventQueue();
		mEventQueue->registerWindowListener(this);
		mEventQueue->registerKeyListener(this);
		mEventQueue->registerMouseListener(this);

		window->show();

		mModel = new MyPaintingModel(mGraphicsManager);

		mView = new MyPaintingView(window, mModel);

		MyPaintingControllerState *state = new MyPaintingControllerState(CS_MAIN, this, mModel, mView);
		this->addState(state);
		this->setDefaultState(state);
		this->execute();
	}

	~MyPaintingController()
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
	MyPaintingModel					*mModel;
	AE::PluginManager				*mPluginManager;
	AE::OS::WindowManager			*mWindowManager;
	MyPaintingView					*mView;
};



void ExampleTestSuite::paintingTest()
{
	MyPaintingController *controller = new MyPaintingController();

	controller->execute();

	delete controller;
}