//
//  AppleNavigatorFactory.m
//
//  Created by Mikhail Krasnorutskiy on 20/12/19.
//

#include "AppleNavigatorFactory.h"
#include "AppleNavigator.hpp"

using namespace std;

shared_ptr<Navigator> AppleNavigatorFactory::createNavigator(shared_ptr<Controller> rootController)
{
    auto navigator = make_shared<AppleNavigator>();
    navigator->setRootController(rootController);
    
    return navigator;
}
