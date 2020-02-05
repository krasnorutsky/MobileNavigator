//
//  MyNavController.m
//
//  Created by Михаил Красноруцкий on 07.02.15.
//
//

#import "MyNavController.h"
#include "Navigator.hpp"

using namespace std;

@implementation MyNavController

static MyNavController* controller = nil;

+(MyNavController*)instance
{
    return controller;
}

-(id)initWithCoder:(NSCoder *)aDecoder
{
    if (self = [super initWithCoder:aDecoder])
    {
        [[UIApplication sharedApplication].delegate window].backgroundColor = [UIColor whiteColor];
        
        self.delegate = self;
        
        controller = self;
    }

    return self;
}

-(void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
}

@end
