//
//  Navigator.hpp
//
//  Created by Mikhail Krasnorutsky on 15/04/2019.
//

#ifndef Navigator_hpp
#define Navigator_hpp

#include "Controller.hpp"
#include <vector>
#include <memory>

class Navigator
{
protected:
    static std::shared_ptr<Navigator> navigator;

private:
    std::shared_ptr<Controller> rootController;
    
    virtual void showMessageBoxOK_(std::string title, std::string message) {};
    
    //For android LoginController -> MainActivity
    virtual bool push_(std::shared_ptr<Controller> parent,
                       std::shared_ptr<Controller> child,
                       bool animated) {return false; }
    virtual bool pop_(std::shared_ptr<Controller> c,
                      bool animated) {return false; }
    virtual void removeAutoPoppedControllers_() {};
    
    virtual bool addNativeChildController_(std::shared_ptr<Controller> child, std::shared_ptr<Controller> parent) { return false; }
    virtual void removeNativeChildController_(std::shared_ptr<Controller> child, std::shared_ptr<Controller> parent) {};
    
    virtual void setTitleString_(std::shared_ptr<Controller> c, std::string title) {};

public:
    void setRootController(std::shared_ptr<Controller> rootController);
    
    void setParentController(std::shared_ptr<Controller> child,
                             std::shared_ptr<Controller> parent)
    {
        child->parent = parent;
    }

    static void setNavigator(std::shared_ptr<Navigator> theNavigator)
    {
        navigator = theNavigator;
    }
    
    static void setLoginControllerDelegate(std::shared_ptr<Navigator> theNavigator)
    {
        navigator = theNavigator;
    }
    
    static void showMessageBoxOK(std::string title, std::string message);
    
    static bool push(std::shared_ptr<Controller> parent,
                      std::shared_ptr<Controller> child,
                      bool animated=true);
    static bool pop(std::shared_ptr<Controller> c,
                     bool animated=true);
    static void removeAutoPoppedControllers()
    {
        navigator->removeAutoPoppedControllers_();
    }
    
    static bool addNativeChildController(std::shared_ptr<Controller> child, std::shared_ptr<Controller> parent)
    {
        return navigator->addNativeChildController_(child, parent);
    }
    
    static void removeNativeChildController(std::shared_ptr<Controller> child, std::shared_ptr<Controller> parent)
    {
        navigator->removeNativeChildController_(child, parent);
    }
    
    static void setTitleString(std::shared_ptr<Controller> c, std::string title)
    {
        navigator->setTitleString_(c, title);
    }
    
    template<typename D>
    static void push(std::shared_ptr<D> data, bool animated=true)
    {
        std::shared_ptr<Controller> parent;
        push(parent, std::dynamic_pointer_cast<Controller>(data), animated);
    }
    
    static void pop(bool animated=true)
    {
        std::shared_ptr<Controller> parent;
        pop(parent, animated);
    }
};

#endif /* Navigator_hpp */
