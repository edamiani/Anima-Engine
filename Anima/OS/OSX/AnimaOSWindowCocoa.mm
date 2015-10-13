//
//  AnimaOSWindowCocoa.cpp
//  TesteCocoa1
//
//  Created by Edgard on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "AnimaOSWindowCocoa.h"

namespace AE
{
    namespace OS
    {
        WindowCocoa::WindowCocoa(MyApplication *app, const std::string &windowTitle, const AE::OS::WindowDesc &windowDesc)
            : Window(windowTitle, windowDesc)
        {
            mWindow = [[AnimaOSWindowCocoaBase alloc] init];
            [mWindow setApplication:app];
        }
        
        WindowCocoa::~WindowCocoa()
        {
            
        }
    }
}
