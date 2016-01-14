//
//  AnimTreeState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/14/16.
//
//

#include "AnimTreeState.h"
#include "../../../DEFINES.h"

AnimTreeState::AnimTreeState()
{
    m_defaultState = false;
    m_loop = false;
}

AnimTreeState::~AnimTreeState()
{
    
}

void AnimTreeState::DNADataInit( const rapidjson::Value& i_dnaObject )
{
    ASSERTS( i_dnaObject.HasMember( "name" ), "AnimTreeState missing 'name'!" );
    ASSERTS( i_dnaObject.HasMember( "defaultState" ), "AnimTreeState missing 'defaultState'!" );
    ASSERTS( i_dnaObject.HasMember( "motion" ), "AnimTreeState missing 'motion'!" );
    ASSERTS( i_dnaObject.HasMember( "loop" ), "AnimTreeState missing 'loop'!" );
    ASSERTS( i_dnaObject.HasMember( "onExit" ), "AnimTreeState missing 'onExit'!" );
    ASSERTS( i_dnaObject.HasMember( "events" ), "AnimTreeState missing 'events'!" );
    ASSERTS( i_dnaObject.HasMember( "ignoreEvents" ), "AnimTreeState missing 'ignoreEvents'!" );
    
    m_name = i_dnaObject["name"].GetString();
    m_defaultState = i_dnaObject["defaultState"].GetBool();
    m_motionName = i_dnaObject["motion"].GetString();
    m_loop = i_dnaObject["loop"].GetBool();
    m_onExit = i_dnaObject["onExit"].GetString();
    for ( rapidjson::Value::ConstValueIterator itr = i_dnaObject["events"].Begin(); itr != i_dnaObject["events"].End(); ++itr )
    {
        m_events.push_back( itr->GetString() );
    }
    for ( rapidjson::Value::ConstValueIterator itr = i_dnaObject["ignoreEvents"].Begin(); itr != i_dnaObject["ignoreEvents"].End(); ++itr )
    {
        m_ignoreEvents.push_back( itr->GetString() );
    }
}

bool AnimTreeState::RespondsToEvent( std::string i_event )
{
    return std::find( m_events.begin(), m_events.end(), i_event ) != m_events.end();
}

bool AnimTreeState::IgnoresEvent( std::string i_event )
{
    return std::find( m_ignoreEvents.begin(), m_ignoreEvents.end(), i_event ) != m_ignoreEvents.end();
}