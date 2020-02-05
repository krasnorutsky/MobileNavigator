//
//  Navigator.cpp
//
//  Created by Mikhail Krasnorutsky on 19/04/2019.
//

#include "Navigator.hpp"
#include "NavigatorFactory.hpp"

using namespace std;

shared_ptr<Navigator> Navigator::navigator;

void Navigator::setRootController(std::shared_ptr<Controller> rootController)
{
    push_(nullptr, rootController, false);
}

void Navigator::showMessageBoxOK(string title, string message)
{
    navigator->showMessageBoxOK_(title, message);
}

bool Navigator::push(shared_ptr<Controller> parent,
                     shared_ptr<Controller> child,
                     bool animated)
{
    return navigator->push_(parent, child, animated);
}

bool Navigator::pop(shared_ptr<Controller> c,
                    bool animated)
{
    return navigator->pop_(c,animated);
}
