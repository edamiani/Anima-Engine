//
//  AnimaGraphicsDeviceContextOSX.h
//  TesteCocoa1
//
//  Created by Edgard on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//#include "AnimaOSWindowCocoa.h"

#import <Foundation/Foundation.h>

/*namespace AE
{
    namespace Graphics
    {
        namespace Device
        {
            class ContextCocoaImpl
            {
            public:
                ContextCocoaImpl(NSWindow *windowCocoa);
                ~ContextCocoaImpl();
                
            protected:
                NSOpenGLView *mOpenGLView;
            };
        }
    }
}*/

@interface AnimaGraphicsDeviceContextCocoaImpl : NSObject
{
    NSOpenGLView *mOpenGLView;
}

- (void) init:(NSWindow *)windowCocoa;

@end
