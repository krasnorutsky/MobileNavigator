//
//  AppleNavigatorFactory.h
//
//  Created by Mikhail Krasnorutskiy on 20/12/19.
//

#include "NavigatorFactory.hpp"

class AppleNavigatorFactory : public NavigatorFactory
{
public:
    virtual std::shared_ptr<Navigator> createNavigator(std::shared_ptr<Controller> rootController) override;
};
