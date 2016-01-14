//
//  EventManager.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//
#include "cocos2d.h"
#include "../../DEFINES.h"

#include "EventManager.h"

EventManager* EventManager::s_instance;

EventManager* EventManager::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new EventManager();
    }
    return s_instance;
}

void EventManager::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void EventManager::SendEvent( std::string i_name, void* i_data )
{
    cocos2d::EventCustom event( i_name );
    event.setUserData( i_data );
    cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent( &event );
}

void EventManager::RegisterForEvent( const std::string i_name, const std::function<void(cocos2d::EventCustom*)> &i_callback, void* i_target )
{
    cocos2d::EventListenerCustom* pListener = cocos2d::EventListenerCustom::create( i_name, i_callback );
    cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority( pListener, 1 );
    
    std::map<std::string, cocos2d::EventListenerCustom*> pListenerMap;
    if ( m_listeners.find( i_target ) != m_listeners.end() )
    {
        pListenerMap = m_listeners.at( i_target );
        m_listeners.erase( i_target );
    }
    
    pListenerMap.insert( { i_name, pListener } );
    m_listeners.insert( { i_target, pListenerMap } );
}

void EventManager::UnregisterForEvent( const std::string i_name, void* i_target )
{
    std::map<std::string, cocos2d::EventListenerCustom*> pListenerMap = m_listeners.at( i_target );
    m_listeners.erase( i_target );
    cocos2d::EventListenerCustom* pListener = pListenerMap.at( i_name );
    ASSERTS( pListener, "Unregistering nonexistant event listener!");
    if ( pListener )
    {
        cocos2d::Director::getInstance()->getEventDispatcher()->removeEventListener( pListener );
        pListenerMap.erase( i_name );
    }
    if ( pListenerMap.size() > 0 )
    {
        m_listeners.insert( { i_target, pListenerMap } );
    }
}