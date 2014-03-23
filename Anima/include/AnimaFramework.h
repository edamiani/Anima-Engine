#ifndef __AE_FRAMEWORK__
#define __AE_FRAMEWORK__

#include "AnimaPrerequisites.h"
#include "AnimaGraphicsManager.h"
#include "AnimaOSWindow.h"
#include "AnimaInputEvents.h"

#include "OgreTimer.h"

namespace AE
{
	class Framework
	{
	public:
		Framework();
		virtual ~Framework();

		/*// OIS events
		// Keyboard
		virtual bool			keyPressed(const OIS::KeyEvent &arg) = 0;
		virtual bool			keyReleased(const OIS::KeyEvent &arg) = 0;
		//Mouse
		virtual bool			mouseMoved(const OIS::MouseEvent &arg) = 0;
		virtual bool			mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
		virtual bool			mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) = 0;
		// Joystick
		virtual bool			buttonPressed(const OIS::JoyStickEvent &arg, int button) = 0;
		virtual bool			buttonReleased(const OIS::JoyStickEvent &arg, int button) = 0;
		virtual bool			axisMoved(const OIS::JoyStickEvent &arg, int axis) = 0;*/

		// Input events
		virtual void			onJoyAxisMoved(const AE::Input::JoystickEvent &e, int axis) = 0;
		virtual void			onJoyButtonDown(const AE::Input::JoystickEvent &e) = 0;
		virtual void			onJoyButtonUp(const AE::Input::JoystickEvent &e) = 0;
		virtual void			onKeyDown(const AE::Input::KeyEvent &e) = 0;
		virtual void			onKeyUp(const AE::Input::KeyEvent &e) = 0;
		virtual void			onMouseButtonDown(const AE::Input::MouseEvent &e) = 0;
		virtual void			onMouseButtonUp(const AE::Input::MouseEvent &e) = 0;
		virtual void			onMouseMoved(const AE::Input::MouseEvent &e) = 0;

		// Window events
		virtual void			onWindowClosed(AE::OS::WindowMetrics wm) { stop(); }
		virtual bool			onWindowClosing(AE::OS::WindowMetrics wm) { return true; }
		virtual void			onWindowFocusChange(AE::OS::WindowMetrics wm) {}
		virtual void			onWindowMoved(AE::OS::WindowMetrics wm)   {}
		virtual void			onWindowResized(AE::OS::WindowMetrics wm) {}

		// Graphics events
		virtual void			onEnterFrame(float timeSinceLastFrame) = 0;
		virtual void			onSceneFinish() = 0;
		virtual void			onSceneStart() = 0;

		virtual void			createScene(void) {}
		virtual void			destroyScene(void) {}
		AE::Graphics::Manager*	getGraphicsManager() { return mGraphicsManager; }
		AE::Input::Manager*		getInputManager() { return mInputManager; }
		AE::Physics::Manager*	getPhysicsManager() { return mPhysicsManager; }
		AE::OS::Window*			getWindow() { return mWindow; }
		bool					isRealTime() { return mIsRealTime; }
		bool					isRunning() { return mIsRunning; }
		void					play();
		void					setRealTime(bool isRealTime) { mIsRealTime = isRealTime; }
		bool					setup(int width = 640, int height = 480, bool fullScreen = false, AE::Graphics::RenderType renderType = AE::Graphics::RT_OPENGL);
		void					stop() { mIsRunning = false; }
		void					yield();

	protected:
		unsigned long			mCurrentTime;
		bool					mIsRealTime;
		bool					mIsRunning;
		unsigned long			mLastTime;

		AE::Entity::Manager		*mEntityManager;
		AE::Graphics::Manager	*mGraphicsManager;
		AE::Gui::Manager		*mGuiManager;
		AE::Physics::Manager	*mPhysicsManager;
		Ogre::Timer				*mTimer;
		AE::OS::Window			*mWindow;
		AE::Xml::Manager		*mXmlManager;
		
		// Input objects
		AE::Input::Manager		*mInputManager;
		AE::Input::Joystick		*mJoystick;
		AE::Input::Keyboard		*mKeyboard;
		AE::Input::Mouse		*mMouse;

	};
}

#endif