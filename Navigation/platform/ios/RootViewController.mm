//
//  RootViewController.m
//
//  Created by Mikhail Krasnorutskiy on 29/12/19.
//

#import "RootViewController.h"
#import "UIViewController+Categories.h"

#include "Application.hpp"
#include "AppleNavigatorFactory.h"

using namespace std;

@implementation RootViewController

static RootViewController* controller = nil;
    
-(id)initWithCoder:(NSCoder *)aDecoder
{
    if (self = [super initWithCoder:aDecoder])
    {
        controller = self;
    }
    
    return self;
}

+(id)newFromResource
{
    if (!controller)
    {
        [super newFromResource];
    }
    
    return controller;
}

-(void)viewDidLoad
{
    Application::instance().onApplicationStarted(make_shared<AppleNavigatorFactory>());
    
    [super viewDidLoad];
}

@end
