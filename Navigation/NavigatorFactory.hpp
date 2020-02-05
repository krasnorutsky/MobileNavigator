//
//  NavigatorFactory.hpp
//
//  Created by Mikhail Krasnorutskiy on 1/1/20.
//

#ifndef NavigatorFactory_hpp
#define NavigatorFactory_hpp

#include "Navigator.hpp"

class NavigatorFactory
{
public:
    virtual std::shared_ptr<Navigator> createNavigator(std::shared_ptr<Controller> rootController)
    {
        return nullptr;
    }
};

#endif /* NavigatorFactory_hpp */
