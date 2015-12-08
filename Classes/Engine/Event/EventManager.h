//
//  EventManager.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <string>

class EventManager
{
public:
    static void SendEvent( std::string i_name, void* i_data );
};

#endif /* EventManager_hpp */
