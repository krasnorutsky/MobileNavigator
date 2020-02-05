//
//  AppleNavigator.m
//
//  Created by Mikhail Krasnorutskiy on 29/11/19.
//

#include "AppleNavigator.hpp"
#import "NSString+Categories.h"
#import "UIViewController+Categories.h"
#import "MyNavController.h"
#include "ChildViewController.h"
#include <algorithm>
#include <cctype>
#include <vector>
#include <iostream>

using namespace std;

shared_ptr<Controller> AppleNavigator::getControllerById(int idt)
{
    for (auto& [controller, nativeControler] : controllers)
    {
        if (controller->idt() == idt)
        {
            return controller;
        }
    }
    
    return nullptr;
}

BaseViewController* AppleNavigator::getNativeController(shared_ptr<Controller> c)
{
    if (controllers.find(c) == controllers.end())
    {
        return nil;
    }
    
    return controllers[c];
}

ChildViewController* AppleNavigator::getNativeChildController(BaseViewController* nativeController, NSString* controllerName)
{
    for (UIView* c in nativeController.view.subviews)
    {
        if ([c isKindOfClass:[ChildViewController class]] &&
            [NSStringFromClass(c.class) isEqualToString:controllerName])
        {
            return (ChildViewController*)c;
        }
    }
    
    return nil;
}

static string nativeControllerClassName(shared_ptr<Controller> c)
{
    if (!c)
    {
        return "";
    }
    
    auto className = c->className();
    
    string controllerString = "Controller";
    if (className.length() <= controllerString.length())
    {
        return "";
    }
    
    className = className.substr(0, className.length()-controllerString.length()) + "ViewController";
    
    return className;
}

static string nativeChildControllerClassName(shared_ptr<Controller> c)
{
    if (!c)
    {
        return "";
    }
    
    auto className = c->className();
    
    string controllerString = "Controller";
    if (className.length() <= controllerString.length())
    {
        return "";
    }
    
    className = className.substr(0, className.length()-controllerString.length()) + "ViewController";
    
    return className;
}

ChildViewController* AppleNavigator::createNativeChildController(shared_ptr<Controller> c, shared_ptr<Controller> parent)
{
    if (!c ||
        !parent)
    {
        return nil;
    }
    
    auto className = nativeChildControllerClassName(c);
    if (className.empty())
    {
        return nil;
    }
    
    ChildViewController* nativeController = [NSClassFromString(nsString(className)) newFromResource];
    
    return nativeController;
}
    
BaseViewController* AppleNavigator::createNativeController(shared_ptr<Controller> c)
{
    if (!c)
    {
        return nil;
    }
    
    auto className = nativeControllerClassName(c);
    if (className.empty())
    {
        return nil;
    }
    
    BaseViewController* nativeController = [NSClassFromString(nsString(className)) newFromResource];
    
    controllers[c] = nativeController;
    
    return nativeController;
}

bool AppleNavigator::push(BaseViewController* parentController,
                          BaseViewController* controller,
                          bool animated)
{
    if (!controller)
    {
        return false;
    }

    UINavigationController* navVC = parentController ? parentController.navigationController : /*(UINavigationController*)UIApplication.sharedApplication.keyWindow.rootViewController*/[MyNavController instance];
    
    if (navVC.topViewController != controller)
    {
        [navVC pushViewController:controller animated:animated];
    }
    
    return true;
}

bool AppleNavigator::pop(BaseViewController* controller, bool animated)
{
    UINavigationController* navVC = [MyNavController instance]; //(UINavigationController*)UIApplication.sharedApplication.keyWindow.rootViewController;
    
    if (nil==controller ||
        navVC.topViewController == controller)
    {
        [navVC popViewControllerAnimated:animated];
        return true;
    }
    
    return false;
}

bool AppleNavigator::push_(shared_ptr<Controller> parent,
                           shared_ptr<Controller> child,
                           bool animated)
{
    BaseViewController* parentNativeController = getNativeController(parent);
    if (parent)
    {
        if (!parentNativeController)
        {
            return false;
        }
    }
    else
    {
        UINavigationController* navVC = [MyNavController instance];// (UINavigationController*)UIApplication.sharedApplication.keyWindow.rootViewController;
        
        parentNativeController = (BaseViewController*)navVC.topViewController;
        for (auto& [parentC,parentNativeC] : controllers)
        {
            if (parentNativeC == parentNativeController)
            {
                parent = parentC;
                break;
            }
        }
    }
    
    child->onControllerWillBeAdded();
    
    BaseViewController* nativeController = createNativeController(child);
    if (!nativeController)
    {
        return false;
    }
    
    if (!push(parentNativeController, nativeController, animated))
    {
        return false;
    }
    
    setParentController(child, parent);
    nativeController.base_data = child;

    return true;
}

bool AppleNavigator::pop_(shared_ptr<Controller> c,
                          bool animated)
{
    BaseViewController* nativeController = getNativeController(c);
    if (c &&
        !nativeController)
    {
        return false;
    }
    
    if (!pop(nativeController, animated))
    {
        return false;
    }
    
    nativeController.base_data = nullptr;
    controllers.erase(c);
    
    return true;
}

void AppleNavigator::removeAutoPoppedControllers_()
{
    vector<shared_ptr<Controller>> toDelete;
    
    for (auto& [parentC,parentNativeC] : controllers)
    {
        if (!parentNativeC.navigationController)
        {
            toDelete.push_back(parentC);
        }
    }
    
    for (auto& p : toDelete)
    {
        controllers.erase(p);
    }
}

bool AppleNavigator::addNativeChildController_(shared_ptr<Controller> child, shared_ptr<Controller> parent)
{
    if (!parent)
    {
        return false;
    }
    
    BaseViewController* parentNativeController = getNativeController(parent);
    if (!parentNativeController)
    {
        return false;
    }
    
    ChildViewController* childNativeController = createNativeChildController(child, parent);
    if (!childNativeController)
    {
        return false;
    }
    
    if (![parentNativeController addChild:childNativeController])
    {
        cout << "Warning! Failed to add native child view controller '" << child->className() << "' to the parent '" << parent->className() << "'" << endl;
        
        return false;
    }
    
    childNativeController.base_data = child;
    
    return true;
}

void AppleNavigator::removeNativeChildController_(shared_ptr<Controller> child, shared_ptr<Controller> parent)
{
    if (!parent)
    {
        return;
    }
    
    BaseViewController* parentNativeController = getNativeController(parent);
    if (!parentNativeController)
    {
        return;
    }
    
    auto className = nativeChildControllerClassName(child);
    if (className.empty())
    {
        return;
    }
    
    ChildViewController* childNativeController = getNativeChildController(parentNativeController, nsString(className));
    if (!childNativeController)
    {
        return;
    }
    
    [parentNativeController removeChild:childNativeController];
}

void AppleNavigator::setTitleString_(shared_ptr<Controller> c, string title)
{
    BaseViewController* nativeController = getNativeController(c);
    nativeController.title = nsString(title);
}

void AppleNavigator::showMessageBoxOK_(string title, string message)
{
    UIAlertController * alert = [UIAlertController alertControllerWithTitle:nsString(title)
                                                                    message:nsString(message)
                                                             preferredStyle:UIAlertControllerStyleAlert];
    
    UIAlertAction* okButton = [UIAlertAction
                                actionWithTitle:@"OK"
                                style:UIAlertActionStyleDefault
                                handler:^(UIAlertAction * action) {
                            //No handler
                    }];
    
    [alert addAction:okButton];
    
    [[MyNavController instance] presentViewController:alert animated:YES completion:nil];
}

void AppleNavigator::onNativeControllerAttachChild_(ChildViewController* childVC)
{
    auto childClassName = stdString([NSStringFromClass(childVC.class) stringByReplacingOccurrencesOfString:@"View" withString:@"Controller"]);
    
    shared_ptr<Controller> parent;
    
    for (auto& [parentC,parentNativeC] : controllers)
    {
        if ([childVC isDescendantOfView:parentNativeC.view])
        {
            parent = parentC;
        }
    }
    
    if (!parent)
    {
        return;
    }
    
    for (int i=0; i<parent->childrenCount(); ++i)
    {
        auto childController = parent->childAtIndex(i);
        if (childController->className() == childClassName)
        {
            if (!childVC.base_data)
            {
                childVC.base_data = childController;
            }
            
            break;
        }
    }
}
