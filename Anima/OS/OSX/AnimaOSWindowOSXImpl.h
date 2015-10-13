//
//  AnimaOSWindowOSXImpl.h
//  AnimaOS
//
//#ifdef __OBJC__
#ifndef __AE_OS_WINDOW_OSX_IMPL__
#define __AE_OS_WINDOW_OSX_IMPL__

#include <Cocoa/Cocoa.h>
#include "AnimaOSWindowOSXCocoa.h"

namespace AE
{
	namespace OS
	{
		struct WindowOSXImpl
		{
			WindowOSXImpl()
			{
				//Por enquanto não faz nada
			}
			
			~ WindowOSXImpl()
			{
				//Por enquanto não faz nada
			}
			
			//	WindowRef mWinRef;
			NSWindow *mWindow;
			bool mIsRunning;
			AnimaOSWindowOSXCocoa *mCocoaWindow;
		};
		
		//OSStatus WindowOSXMsgProc(EventHandlerCallRef eventhandler, EventRef event, void *userdata);
	}
}
#endif