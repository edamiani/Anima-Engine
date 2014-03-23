#include "../include/AnimaFramework.h"
#include "../include/AnimaEntityManager.h"
#include "../include/AnimaGraphicsManagerOgre.h"
#include "../include/AnimaInputManagerOIS.h"
#include "../include/AnimaPhysicsManagerBullet.h"
#include "../include/AnimaOSWindowOgre.h"
#include "../include/AnimaGuiManager.h"
#include "../include/AnimaXmlManagerRapidXml.h"

#include <Ogre.h>

namespace AE
{
	Framework::Framework()
	{
		mGraphicsManager = 0;
		mGuiManager = 0;
		mInputManager = 0;
		mIsRealTime = true;
		mIsRunning = false;
		mKeyboard = 0;
		mMouse = 0;
		mPhysicsManager = 0;
		mTimer = 0;
		mXmlManager = 0;
	}

	Framework::~Framework()
	{
		if(mInputManager) delete mInputManager;
		if(mTimer) delete mTimer;
		mWindow = 0;
		if(mGuiManager) delete mGuiManager;
		if(mGraphicsManager) delete mGraphicsManager;
		if(mPhysicsManager) delete mPhysicsManager;
		if(mXmlManager) delete mXmlManager;
	}

	void Framework::play()
	{
		onSceneStart();

		mTimer->reset();
		mCurrentTime = 0;
		mLastTime = 0;

		while(mIsRunning)
		{
			mCurrentTime = mTimer->getMilliseconds();
			onEnterFrame((mCurrentTime - mLastTime) / 1000.0f);
			mPhysicsManager->update((mCurrentTime - mLastTime) / 1000.0f);
			mLastTime = mCurrentTime;

			mGraphicsManager->renderFrame();
		}

		onSceneFinish();

		if(!mIsRealTime)
			yield();
	}

	bool Framework::setup(int width, int height, bool fullScreen, AE::Graphics::RenderType renderType)
	{
		mIsRunning = true;

		mXmlManager = new AE::Xml::ManagerRapidXml();

		mGraphicsManager = new AE::Graphics::ManagerOgre(this, renderType);
		if(!mIsRunning)
			return false;

		mGuiManager = new AE::Gui::Manager();

		mWindow = mGraphicsManager->getWindow();
		mWindow->setFullScreen(fullScreen);
		mTimer = new Ogre::Timer();

		mInputManager = new AE::Input::ManagerOIS();
		mInputManager->initialize(this);
		mJoystick = mInputManager->createJoystick(false);
		mKeyboard = mInputManager->createKeyboard(true);
		mMouse = mInputManager->createMouse(true);

		mPhysicsManager = new AE::Physics::ManagerBullet();
		mPhysicsManager->initialize(this);

		mEntityManager = new AE::Entity::Manager(this);

		//Set initial mouse clipping size
		//windowResized(mWindow);

		return true;
	}

	void Framework::yield()
	{
		mGraphicsManager->yield();
	}
}