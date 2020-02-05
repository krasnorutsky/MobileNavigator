//
//  Controller.hpp
//
//  Created by Mikhail Krasnorutsky on 17/04/2019.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "ControllerEventDelegate.hpp"
#include <string>
#include <functional>
#include <memory>
#include <vector>

#define MAIN_ACTIVITY_IDENTIFIER 1

class Navigator;

class Controller : public std::enable_shared_from_this<Controller>
{
    friend class Navigator;
    
    std::weak_ptr<Controller> parent;
    
    std::string nativeClassName_;
    std::string titleString_;

protected:
    int idt_;
    
    template<typename T>
    std::shared_ptr<T> shared_this()
    {
        return std::static_pointer_cast<T>(shared_from_this());
    }
    
    template<typename T>
    std::weak_ptr<T> weak_this()
    {
        return std::static_pointer_cast<T>(shared_from_this());
    }
    
public:
    Controller(std::string nativeClassName = "");
    
    void setTitleString(std::string title);
    std::string titleString() const
    {
        return titleString_;
    }
    
    int idt() const
    {
        return idt_;
    }

    std::string className() const;
    
    //iOS only
    virtual void viewDidAppear();
    
private:
    std::vector<std::shared_ptr<Controller>> children;
    std::vector<std::weak_ptr<Controller>> childrenUnattached;
    
public:
    void addChild(std::shared_ptr<Controller> child);
    void removeChild(std::shared_ptr<Controller> child);
    void attachNativeToChildren();
        
    int childrenCount();
    
    std::shared_ptr<Controller> childAtIndex(int i);
    
    void setEventDelegate(std::shared_ptr<ControllerEventDelegate> delegate);
    virtual void onControllerWillBeAdded(){};
    
    void postUpdateEvent();
    void postTableUpdateEvent();
private:
    
    std::weak_ptr<ControllerEventDelegate> eventDelegate;
};

#endif /* Controller_hpp */
