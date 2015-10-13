//
//  CocoaWindow.mm
//  AnimaOS
//
//  Created by Robson on 14/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import <stdio.h>
//#import <Cocoa/Cocoa.h>
#import "AnimaOSWindowOSXCocoa.h"

	@implementation AnimaOSWindowOSXCocoa
		-(id)init{
			self = [super init];
			
			if (self){
			
				textoTest = @"Entrou em AnimaOSWindowOSXCocoa";
/*				NSAutoreleasePool *pool = [NSAutoreleasePool new];
				NSApplication *NSApp = [NSApplication sharedApplication];
				NSRect frame = NSMakeRect( 100., 100., 300., 300. );
			
				NSWindow *window = [[NSWindow alloc]
					initWithContentRect:frame
					styleMask:NSTitledWindowMask | NSClosableWindowMask | NSMiniaturizableWindowMask
					backing:NSBackingStoreBuffered
					defer:false];
			
				[window setTitle:@"Hello World!!!"];
			
				NSView *view = [[[self alloc] initWithFrame:frame] autorelease];
				[window setContentView:view];
				[window setDelegate:view];
				[window makeKeyAndOrderFront:nil];
			
			//[NSApp run];
				NSModalSession session = [NSApp beginModalSessionForWindow:self];
					for (;;) {
						if ([NSApp runModalSession:session] != NSRunContinuesResponse)
							break;
						//[self doSomeWork];
					}
				[NSApp endModalSession:session];
			
				[pool release];
				return( EXIT_SUCCESS );		
*/			}
			return self;
		}

		-(void) dealloc 
		{ 
			[super dealloc]; //do not forget to transmit to the superclass 
		}

		-(void)drawRect:(NSRect)rect {
			[[NSColor blueColor] set];
			NSRectFill( [self bounds] );
		}

		-(void)windowWillClose:(NSNotification *)note {
			[[NSApplication sharedApplication] terminate:self];
		}
		
		-(NSString *) textoTest{ return textoTest;}

		-(void)setTextoTest:(NSString *)novoTexto{
			if (textoTest != novoTexto){
				[textoTest release];
				textoTest = [novoTexto retain];
			}
		}
	@end
		
		/*		Funcao para dar stopModal no Loop
		 -(void)EndProcessWindow:(NSApp *)note {
		 [[NSApplication sharedApplication] terminate:self];
		 }*/
		
