//
//  ControllerEventDelegate.cpp
//
//  Created by Mikhail Krasnorutskiy on 9/1/20.
//

#include "ControllerEventDelegate.hpp"

using namespace std;

ControllerEventDelegate::ControllerEventDelegate()
{
}

ControllerEventDelegate::ControllerEventDelegate(function<void()> updateLambda, function<void()> tableUpdateLambda) : onUpdate_(updateLambda), onTableUpdate_(tableUpdateLambda)
{
}

void ControllerEventDelegate::onUpdate()
{
    if (onUpdate_)
    {
        onUpdate_();
    }
}

void ControllerEventDelegate::onTableUpdate()
{
    if (onTableUpdate_)
    {
        onTableUpdate_();
    }
}
