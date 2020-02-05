//
//  ChildViewController.h
//
//  Created by Mikhail Krasnorutskiy on 29/12/19.
//

#import <UIKit/UIKit.h>
#include <memory>
#include "Controller.hpp"
#include "AppleControllerMacros.h"

@interface ChildViewController : UIView

+(id)newFromResource;

-(void)onUpdateEvent;
-(void)onTableUpdateEvent;

@property (nonatomic,assign) std::shared_ptr<Controller> base_data;

@end
