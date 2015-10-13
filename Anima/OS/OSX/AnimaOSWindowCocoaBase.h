//
//  AnimaOSWindow.h
//  TesteCocoa1
//
//  Created by Gregório Benatti on 26/01/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

//#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

@interface MyApplication : NSApplication 
{
@private
    BOOL shouldKeepRunning;
}

- (void) run;
- (void) finishApp;

@end

@interface AnimaOSWindowCocoaBase : NSNotificationCenter <NSApplicationDelegate>
{
@private
    NSWindow *mWindow;
    MyApplication *mApp;
}

@property (nonatomic, retain) NSWindow *mWindow;

- (id) init;

-(void) setApplication : (NSApplication *)app;

-(NSWindow *) getWindow;

@end
