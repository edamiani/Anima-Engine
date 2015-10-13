//
//  AnimaOSWindowCocoa.h
//  TesteCocoa1
//
//  Created by Edgard on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __ANIMA_OS_WINDOW_COCOA__
#define __ANIMA_OS_WINDOW_COCOA__

#include "AnimaOSWindowCocoaBase.h"
#include "AnimaOSWindow.h"

#import <Cocoa/Cocoa.h>

namespace AE
{
    namespace OS
    {
        class WindowCocoa : public AE::OS::Window
        {
        public:
            WindowCocoa(MyApplication *app, const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc);
            ~WindowCocoa();
            
            virtual void				close() {}
			virtual size_t				getWindowHandle() { return 0; }
			virtual void                render() {}
			virtual void				show() {}
            
            NSWindow* _getCocoaWindow() 
            { 
                NSWindow *window = [mWindow getWindow];
                
                return window; 
            }
            
        protected:
            AnimaOSWindowCocoaBase *mWindow;
            MyApplication *mApp;
        };
    }
}

#endif
