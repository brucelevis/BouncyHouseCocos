//
//  AISystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AIComponent.h"
#include "AISystem.h"

AISystem* AISystem::s_instance;

AISystem* AISystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new AISystem();
    }
    return s_instance;
}

void AISystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void AISystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void AISystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void AISystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        AIComponent* pComponent = (AIComponent*) it->second;
        if ( pComponent )
        {
            pComponent->Update( i_dt );
        }
    }
}

AIBrainState* AISystem::CreateBrainState( std::string i_stateName )
{
    AIBrainStateMap::iterator it = m_brainStateTypes.find( i_stateName );
    if ( it == m_brainStateTypes.end() )
        return NULL;
    
    AIBrainState* pState = it->second();
    return pState;
}


