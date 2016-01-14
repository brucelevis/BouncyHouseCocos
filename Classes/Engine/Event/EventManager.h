//
//  EventManager.hpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <map>
#include <string>
#include "cocos2d.h"

class EventManager
{
public:
    static EventManager* GetInstance();
    static void DestroyInstance();
    
    void SendEvent( std::string i_name, void* i_data );
    void RegisterForEvent( const std::string i_name, const std::function<void(cocos2d::EventCustom*)> &i_callback, void* i_target );
    void UnregisterForEvent( const std::string i_name, void* i_target );

private:
    static EventManager* s_instance;
    std::map<void*, std::map<std::string, cocos2d::EventListenerCustom*>> m_listeners;
};

#endif /* EventManager_hpp */
