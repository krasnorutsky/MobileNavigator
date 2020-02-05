//
//  ChildViewController.m
//
//  Created by Mikhail Krasnorutskiy on 29/12/19.
//

#import "ChildViewController.h"
#include "Navigator.hpp"
#include "AppleNavigator.hpp"
#include "tools.hpp"

using namespace std;

@implementation ChildViewController
{
    std::shared_ptr<ControllerEventDelegate> eventDelegate;
}

+(id)newFromResource
{
    NSString* className = NSStringFromClass([self class]);
    if ([[NSBundle mainBundle]pathForResource:className ofType:@"nib"])
    {
        return [[[NSBundle mainBundle] loadNibNamed:className owner:self options:nil] objectAtIndex:0];
    }
    
    return [[self class] new];
}

-(void)awakeFromNib
{
    [super awakeFromNib];
}

-(void)setBase_data:(std::shared_ptr<Controller>)base_data
{
    _base_data = base_data;
    
    if (_base_data)
    {
        OBJC_WEAKSELF
        eventDelegate = make_shared<ControllerEventDelegate>([weakSelf]()
        {
            [weakSelf onUpdateEvent];
        },
        [weakSelf]()
        {
            [weakSelf onTableUpdateEvent];
        });
    
        _base_data->setEventDelegate(eventDelegate);
    }
}

-(void)onUpdateEvent
{
}

-(void)onTableUpdateEvent
{
}

- (void)didMoveToSuperview
{
    [super didMoveToSuperview];
    
    if (self.superview)//viewDidAppear
    {
        AppleNavigator::onNativeControllerAttachChild(self);
        
        weak_ptr<Controller> weakBaseData = _base_data;
        dispatch_async(dispatch_get_main_queue(), ^{
            
            if (auto base_data_ = weakBaseData.lock())
            {
                base_data_->viewDidAppear();
            }
        });
    }
}

@end
