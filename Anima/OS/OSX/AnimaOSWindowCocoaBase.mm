//
//  AnimaOSWindow.m
//  TesteCocoa1
//
//  Created by Gregório Benatti on 26/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#import "AnimaOSWindowCocoaBase.h"
//#import "AnimaGraphicsDeviceContext.h"

@implementation MyApplication : NSApplication

- (void)run
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    
    shouldKeepRunning = YES;
    do
    {
        [pool release];
        pool = [[NSAutoreleasePool alloc] init];
        
        NSEvent *event =
        [self
         nextEventMatchingMask:NSAnyEventMask
         untilDate:[NSDate distantFuture]
         inMode:NSDefaultRunLoopMode
         dequeue:YES];
        
        [self sendEvent:event];
        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        [self updateWindows];
        glFlush();
    } while (shouldKeepRunning);
    
    [pool release];
}

- (void)finishApp
{
    shouldKeepRunning = NO;
}

@end


@implementation AnimaOSWindowCocoaBase

@synthesize mWindow;

- (id) init
{    
    NSRect windowDimensions = NSMakeRect(50, 50, 150, 150);
    NSWindow *localWindow = [[NSWindow alloc] initWithContentRect:windowDimensions styleMask:NSResizableWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask backing:NSBackingStoreBuffered defer:NO];
    [self setMWindow:localWindow];
    [localWindow release];
    
    NSView *localView = [[NSView alloc] init];
    [mWindow setContentView:localView];
    [localView release];
    
    [mWindow setLevel:NSFloatingWindowLevel];
    [mWindow makeKeyAndOrderFront:self]; 
    //[window setDelegate:self];
    
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowRestored) 
                                                 name:@"NSWindowDidDeminiaturizeNotification" 
                                               object:mWindow];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowMinimized) 
                                                 name:@"NSWindowDidMiniaturizeNotification"
                                               object:mWindow];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowMoved) 
                                                 name:@"NSWindowDidMoveNotification"
                                               object:mWindow];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowFocus) 
                                                 name:@"NSWindowDidResignMainNotification"
                                               object:mWindow];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowResized) 
                                                 name:@"NSWindowDidResizeNotification"
                                               object:mWindow];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowClosed) 
                                                 name:@"NSWindowWillCloseNotification"
                                               object:mWindow];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowEnterFullScreen) 
                                                 name:@"NSWindowDidEnterFullScreenNotification"
                                               object:mWindow];
    [[NSNotificationCenter defaultCenter] addObserver:self 
                                             selector:@selector(windowExitFullScreen) 
                                                 name:@"NSWindowWillExitFullScreenNotification"
                                               object:mWindow];
    
    return self;
}

- (void)applicationWillFinishLaunching:(NSNotification *)notification 
{
    NSLog(@"Finished Launching %@", notification);
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)application
{
    exit(0);
    
    return true;
}

-(NSWindow *) getWindow
{
    return mWindow;
}

-(void) setApplication : (NSApplication *)app
{
    mApp = (MyApplication *)app;
}

- (BOOL)windowResized
{
    return true;
}

- (BOOL)windowMinimized
{
    return true;
}

- (BOOL)windowRestored
{
    return true;
}

- (BOOL)windowMoved
{
    return true;
}

- (BOOL)windowClosed
{
    [mApp finishApp];
    
    return true;
}

- (BOOL)windowEnterFullScreen
{
    return true;
}

- (BOOL)windowExitFullScreen
{
    return true;
}

- (BOOL)windowFocus
{
    return true;
}


@end
