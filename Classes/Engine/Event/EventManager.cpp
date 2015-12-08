//
//  EventManager.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//
#include "cocos2d.h"

#include "EventManager.h"

void EventManager::SendEvent( std::string i_name, void* i_data )
{
    cocos2d::EventCustom event( i_name );
    event.setUserData( i_data );
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent( &event );
}