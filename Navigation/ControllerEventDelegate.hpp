//
//  ControllerEventDelegate.hpp
//
//  Created by Mikhail Krasnorutskiy on 9/1/20.
//

#ifndef ControllerEventDelegate_hpp
#define ControllerEventDelegate_hpp

#include <functional>

struct ControllerEventDelegate
{
    ControllerEventDelegate();
    ControllerEventDelegate(std::function<void()> updateLambda, std::function<void()> tableUpdateLambda);
    
    virtual void onUpdate();
    virtual void onTableUpdate();
private:
    
    std::function<void()> onUpdate_;
    std::function<void()> onTableUpdate_;
};

#endif /* ControllerEventDelegate_hpp */
