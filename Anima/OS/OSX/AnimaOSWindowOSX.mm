#include "../include/AnimaOSWindowOSX.h"
#import "../include/AnimaOSWindowOSXImpl.h"
#include <cassert>

//#include <Cocoa/Cocoa.h>

//[NSApplication sharedApplication];
//#import "AnimaOSWindowOSXImpl.h"
namespace AE
{
	namespace OS
	{

/*		OSStatus WindowOSXMsgProc(EventHandlerCallRef eventhandler, EventRef event, void *userdata)
		{
			OSStatus result = eventNotHandledErr;
			HICommand command;
			UInt32 eventClass, eventKind;
			char keyCode;
			
			eventClass = GetEventClass(event); 
			eventKind = GetEventKind(event);
			
			AE::OS::WindowOSX *window = reinterpret_cast<AE::OS::WindowOSX *>(userdata);
			if(!window) return eventNotHandledErr;
			
			switch (eventClass)
			{
				case kCoreEventClass:
					switch (eventKind)
				{
					case kAEQuitApplication:
						if(window) window->onClose();
						break;
				}
					break;
				case kEventClassKeyboard:
					switch(eventKind)
				{
					case kEventRawKeyDown:
						GetEventParameter(event, kEventParamKeyMacCharCodes, typeChar, nil, sizeof(keyCode), nil, &keyCode);
						if (keyCode == 27)
						{
							if(window) window->onClose();
						}
						break;
				}
					break;
			}
			
			return result;
		}
*/
		WindowOSX::WindowOSX(const std::string &windowTitle, const AE::Math::Point2 &dimensions)
		{
			mWindowOSXImpl = new AE::OS::WindowOSXImpl();
			
			mWindowOSXImpl->mCocoaWindow = [[mCocoaWindow alloc] init];
			
			// restante do construtor

/*			[mWindow setTitle:[NSString stringWithCString:windowTitle.c_str() encoding:NSUTF8StringEncoding]];
			
			// Show window
			if(mWindow)
				[mWindow makeKeyAndOrderFront:nil];
*/			
/*			Rect windowRect;
			int	windowAttributes;
			
			windowRect.left = mWindowMetrics.left;
			windowRect.top = mWindowMetrics.top;
			windowRect.right = mWindowMetrics.left + mWindowMetrics.width;
			windowRect.bottom = mWindowMetrics.top + mWindowMetrics.height;
			
			SetRect(&windowRect, 10, 60, 800, 600);
			
			windowAttributes = kWindowStandardHandlerAttribute | kWindowCloseBoxAttribute | kWindowCollapseBoxAttribute | kWindowResizableAttribute | kWindowStandardDocumentAttributes;
			
			CreateNewWindow(kDocumentWindowClass, windowAttributes, &windowRect, &mWinRef);
			
			SetThemeWindowBackground(mWinRef, kThemeBrushBlack, true);
			
			CFStringRef titleRef = CFStringCreateWithCString( kCFAllocatorDefault, windowTitle, kCFStringEncodingASCII);
			SetWindowTitleWithCFString(mWinRef, titleRef);
			
			InstallStandardEventHandler(GetWindowEventTarget(mWinRef));
			
			const EventTypeSpec myHandleEvents[] =
			{
				{ kCoreEventClass, kAEQuitApplication },
				{ kEventClassKeyboard, kEventRawKeyDown },
				{ kEventClassKeyboard, kEventRawKeyUp },
				{ kEventClassKeyboard, kEventRawKeyModifiersChanged }
			};
			EventHandlerUPP myHandlerUPP = NewEventHandlerUPP(WindowOSXMsgProc);
			InstallEventHandler(GetApplicationEventTarget(), myHandlerUPP, GetEventTypeCount(myHandleEvents), myHandleEvents, this, NULL);
			
			ShowWindow(mWinRef);
			
			mIsRunning = true;
*/		}
		
//		WindowOSX::~WindowOSX() {  }

		WindowOSX::~WindowOSX()
		{
			//mWindowOSXImpl->mCocoaWindow[stopModalWithCode ]
			
			delete mWindowOSXImpl;
			
			//stopModalWithCode - no destrutor.

			// restante do destrutor
		}
		
		
		bool WindowOSX::dispatchNextMessage()
		{
/*			UpdateSystemActivity(UsrActivity);
			
			EventRecord event;
			RgnHandle cursorRgn = NULL;
			Boolean gotEvent = WaitNextEvent(everyEvent, &event, 0, cursorRgn);
			if (gotEvent)
			{
				AEProcessAppleEvent(&event);
			}
			return mIsRunning;*/
			return true;
		}
		
/*		const WindowRef& WindowOSX::getWindowHandle() 
		{
			return mWinRef;
		}
*/		
		bool WindowOSX::waitAndDispatchNextMessage()
		{
/*			EventRecord event;
			RgnHandle cursorRgn = NULL;
			while (mIsRunning)
			{
				UpdateSystemActivity(UsrActivity);
				
				Boolean gotEvent = WaitNextEvent(everyEvent, &event, 0, cursorRgn);
				if (gotEvent)
				{
					AEProcessAppleEvent(&event);
			
					return true;
				}
			}
			return false;
*/		return true;
		}
	}
}