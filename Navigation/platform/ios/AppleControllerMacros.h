//
//  AppleControllerMacros.h
//
//  Created by Mikhail Krasnorutskiy on 29/12/19.
//

#ifndef AppleControllerMacros_h
#define AppleControllerMacros_h

#ifndef SET_DATA_POINTER
#define SET_DATA_POINTER(className)\
{\
    std::shared_ptr<className> _data;\
}\
\
-(void)setBase_data:(std::shared_ptr<Controller>)base_data\
{\
    _data = std::dynamic_pointer_cast<className>(base_data);\
    assert(!base_data || _data);\
    [super setBase_data:base_data];\
}\

#define SET_DATA_POINTER_FOR_BASE_CLASS(className)\
{\
    std::shared_ptr<className> _source_data;\
}\
\
-(void)setBase_data:(std::shared_ptr<Controller>)base_data\
{\
    _source_data = std::dynamic_pointer_cast<className>(base_data);\
    assert(!base_data || _source_data);\
    [super setBase_data:base_data];\
}\

#endif

#endif /* AppleControllerMacros_h */
