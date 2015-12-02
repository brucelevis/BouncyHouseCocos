//
//  GroundDetectSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "GroundDetectSystem.h"

std::map<EntityHandle, Component*> GroundDetectSystem::m_components;

void GroundDetectSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void GroundDetectSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}
void GroundDetectSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        GroundDetectSystem* pComponent = (GroundDetectSystem*) it->second;
        if ( pComponent )
        {
            
        }
    }
}