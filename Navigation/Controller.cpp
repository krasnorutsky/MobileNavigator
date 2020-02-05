//
//  Controller.cpp
//
//  Created by Mikhail Krasnorutsky on 06/05/2019.
//

#include "Controller.hpp"
#include "Navigator.hpp"
#include <iostream>

using namespace std;

Controller::Controller(string nativeClassName) : nativeClassName_(nativeClassName)
{
    static int currentIdt = 1;
    idt_ = currentIdt++;
}

void Controller::setTitleString(string title)
{
    titleString_ = title;
}

string Controller::className() const
{
    string name = typeid(*this).name();
    
    for (int i=(int)name.size()-1; i>=0; --i)
    {
        if (!isalpha(name.at(i)))
        {
            return name.substr(i+1);
        }
    }
    
    return name;
}

void Controller::viewDidAppear()
{
    attachNativeToChildren();
}

void Controller::addChild(std::shared_ptr<Controller> child)
{
    for (auto& c : children)
    {
        if (c->className() == child->className())
        {
            cout << "Error. Attempt to add a second instance of Controller of class '" << child->className() << "' to a parent of class '" << className() << "'" << endl;
            
            return;
        }
    }
    
    child->onControllerWillBeAdded();
    children.push_back(child);
    
    if (!Navigator::addNativeChildController(child, shared_from_this()))
    {
        childrenUnattached.push_back(child);
    }
}

void Controller::removeChild(std::shared_ptr<Controller> child)
{
    Navigator::removeNativeChildController(child, shared_from_this());
    
    for (auto i=children.begin(); i!=children.end(); ++i)
    {
        if (child == *i)
        {
            children.erase(i);
            break;
        }
    }
}

void Controller::attachNativeToChildren()
{
    for (auto child : childrenUnattached)
    {
        if (auto child_ = child.lock())
        {
            Navigator::addNativeChildController(child_, shared_from_this());
        }
    }
    
    childrenUnattached.clear();
}

int Controller::childrenCount()
{
    return (int)children.size();
}

shared_ptr<Controller> Controller::childAtIndex(int i)
{
    if (i < 0 ||
        i >= children.size())
    {
        return nullptr;
    }
    
    return children[i];
}

void Controller::setEventDelegate(std::shared_ptr<ControllerEventDelegate> delegate)
{
    eventDelegate = delegate;
}

void Controller::postUpdateEvent()
{
    if (auto delegate = eventDelegate.lock())
    {
        delegate->onUpdate();
    }
}

void Controller::postTableUpdateEvent()
{
    if (auto delegate = eventDelegate.lock())
    {
        delegate->onTableUpdate();
    }
}
