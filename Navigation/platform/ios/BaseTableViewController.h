//
//  BaseTableViewController.h
//
//  Created by Mikhail Krasnorutskiy on 29/11/19.
//

#import <UIKit/UIKit.h>

#include <memory>
#include "Controller.hpp"
#include "AppleControllerMacros.h"

@class ChildViewController;

@interface BaseTableViewController : UITableViewController

-(void)onUpdateEvent;
-(void)onTableUpdateEvent;

-(BOOL)addChild:(ChildViewController*)child;

@property (nonatomic,assign) std::shared_ptr<Controller> base_data;

@end
