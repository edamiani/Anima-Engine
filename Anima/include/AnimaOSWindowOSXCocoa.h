//
//  CocoaWindow.h
//  AnimaOS
//
//  Created by Robson on 14/04/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

/*		@protocol AE::OS::CocoaWindow
		@end 
		
		@protocol NSView 
			-(void)drawRect:(NSRect)rect; 
		@end
*/		//trocar nome DrawingContextCocoa
		@interface AnimaOSWindowOSXCocoa:NSView
		{
			NSString *textoTest;
		}
			-(id) init;
			-(void) dealloc;
			-(void) drawRect:(NSRect)rect;
			-(NSString *)textoTest;
			-(void)setTextoTest: (NSString *)novoTexto;
		@end
