//
//  BaseTableViewController.m
//
//  Created by Mikhail Krasnorutskiy on 29/11/19.
//

#import "BaseTableViewController.h"
#import "Navigator.hpp"
#import "UIViewController+Categories.h"
#include "tools.hpp"

using namespace std;

@implementation BaseTableViewController
{
    std::shared_ptr<ControllerEventDelegate> eventDelegate;
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    if (_base_data)
    {
        auto title = _base_data->titleString();
        if (!title.empty())
        {
            self.titleString = title;
        }
    }
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

-(void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    
    weak_ptr<Controller> weakBaseData = _base_data;
    dispatch_async(dispatch_get_main_queue(), ^{
        
        if (auto base_data_ = weakBaseData.lock())
        {
            base_data_->viewDidAppear();
        }
    });
}

-(void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];
    
    if (self.isMovingFromParentViewController)
    {
        Navigator::removeAutoPoppedControllers();
    }
}

-(BOOL)addChild:(ChildViewController*)child
{
    return NO;
}

-(void)removeChild:(ChildViewController*)child
{
}

@end
