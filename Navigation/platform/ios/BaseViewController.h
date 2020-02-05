//
//  BaseViewController.h
//
//  Created by Mikhail Krasnorutskiy on 29/11/19.
//

#import <UIKit/UIKit.h>

#include <memory>
#include "Controller.hpp"
#include "AppleControllerMacros.h"

@class ChildViewController;

@interface BaseViewController : UIViewController

-(void)onUpdateEvent;
-(void)onTableUpdateEvent;

-(BOOL)addChild:(ChildViewController*)child;
-(void)removeChild:(ChildViewController*)child;

@property (nonatomic,assign) std::shared_ptr<Controller> base_data;

@end
