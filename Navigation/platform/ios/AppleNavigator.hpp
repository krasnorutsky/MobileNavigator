//
//  AppleNavigator.h
//
//  Created by Mikhail Krasnorutskiy on 29/11/19.
//
#import "BaseViewController.h"

#include <map>
#include "Navigator.hpp"

@class ChildViewController;

class AppleNavigator : public Navigator
{
    std::map<std::shared_ptr<Controller>, BaseViewController*> controllers;
 
    std::shared_ptr<Controller> getControllerById(int idt);
    
    ChildViewController* getNativeChildController(BaseViewController* nativeController, NSString* controllerName);
    BaseViewController* getNativeController(std::shared_ptr<Controller> c);
    ChildViewController* createNativeChildController(std::shared_ptr<Controller> c, std::shared_ptr<Controller> parent);
    BaseViewController* createNativeController(std::shared_ptr<Controller> c);
    
    bool push(BaseViewController* parentController, BaseViewController* controller, bool animated);
    bool pop(BaseViewController* controller, bool animated);
    
    virtual bool push_(std::shared_ptr<Controller> parent,
                       std::shared_ptr<Controller> child,
                       bool animated) override;
    
    virtual bool pop_(std::shared_ptr<Controller> c,
                      bool animated) override;
    
    virtual void removeAutoPoppedControllers_() override;
    
    virtual bool addNativeChildController_(std::shared_ptr<Controller> child, std::shared_ptr<Controller> parent) override;
    virtual void removeNativeChildController_(std::shared_ptr<Controller> child, std::shared_ptr<Controller> parent) override;
    
    virtual void setTitleString_(std::shared_ptr<Controller> c, std::string title) override;
    virtual void showMessageBoxOK_(std::string title, std::string message) override;
    
    void onNativeControllerAttachChild_(ChildViewController* childVC);
public:
    static void onNativeControllerAttachChild(ChildViewController* childVC)
    {
        std::dynamic_pointer_cast<AppleNavigator>(navigator)->onNativeControllerAttachChild_(childVC);
    }
};
