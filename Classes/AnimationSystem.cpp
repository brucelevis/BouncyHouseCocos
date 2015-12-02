//
//  AnimationSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "AnimationComponent.h"
#include "AnimationSystem.h"

std::map<EntityHandle, Component*> AnimationSystem::m_components;

void AnimationSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void AnimationSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}
void AnimationSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        AnimationComponent* pComponent = (AnimationComponent*) it->second;
        if ( pComponent )
        {

        }
    }
}