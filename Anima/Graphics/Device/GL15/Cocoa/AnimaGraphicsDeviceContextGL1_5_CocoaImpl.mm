//
//  AnimaGraphicsDeviceContextOSX.mm
//  TesteCocoa1
//
//  Created by Edgard on 2/5/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "../include/AnimaGraphicsDeviceContextCocoaImpl.h"

@implementation AnimaGraphicsDeviceContextCocoaImpl

- (void) init:(NSWindow *)windowCocoa
{
    NSRect contentRect = [windowCocoa contentRectForFrameRect:[windowCocoa frame]];
    //NSRect contentRect = [window frameRectForContentRect:[window frame]];
                
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[40];
    NSOpenGLPixelFormat *pixelFormat = nil;
    
    // Pixel Format Attributes for the windowed NSOpenGLContext
    int i = 0;
    //pixelFormatAttributes[i++] = NSOpenGLPFAAllRenderers;
    pixelFormatAttributes[i++] = NSOpenGLPFADoubleBuffer;
    //pixelFormatAttributes[i++] = NSOpenGLPFAStereo;
    //pixelFormatAttributes[i++] = NSOpenGLPFAAuxBuffers;
    //pixelFormatAttributes[i++] = NSOpenGLPFAColorSize;
    //pixelFormatAttributes[i++] = NSOpenGLPFAAlphaSize;
    //pixelFormatAttributes[i++] = NSOpenGLPFADepthSize;
    //pixelFormatAttributes[i++] = NSOpenGLPFAStencilSize;
    //pixelFormatAttributes[i++] = NSOpenGLPFAAccumSize;
    //pixelFormatAttributes[i++] = NSOpenGLPFAMinimumPolicy;
    //pixelFormatAttributes[i++] = NSOpenGLPFAMaximumPolicy;
    //pixelFormatAttributes[i++] = NSOpenGLPFAOffScreen;
    //pixelFormatAttributes[i++] = NSOpenGLPFAOffScreen;
    
    pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    
    mOpenGLView = [[NSOpenGLView alloc] initWithFrame:contentRect pixelFormat:pixelFormat];
    
    [pixelFormat release];
    
    [windowCocoa setContentView:mOpenGLView];
    [windowCocoa setInitialFirstResponder:mOpenGLView];
    [windowCocoa setReleasedWhenClosed:NO];
    
    [mOpenGLView prepareOpenGL];
    [[mOpenGLView openGLContext] makeCurrentContext];
    [[mOpenGLView openGLContext] update];
    
    glClearColor(1.0, 0.0, 0.0, 1.0);
    //glClear(glClearColor(1.0, 0.0, 0.0, 1.0));
    //glClear(glClearColor);
    
    [mOpenGLView display];
}
            
- (void) dealloc
{
    [mOpenGLView dealloc];       
}
@end