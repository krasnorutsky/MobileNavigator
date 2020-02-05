//
//  MyNavController.h
//
//  Created by Mikhail Krasnorutskiy on 20/12/19.
//

#import <UIKit/UIKit.h>
#include "Navigator.hpp"

@interface  MyNavController : UINavigationController<UINavigationControllerDelegate>

+(MyNavController*)instance;

@end
