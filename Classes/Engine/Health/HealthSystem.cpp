//
//  HealthSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/5/15.
//
//

#include "HealthComponent.h"
#include "HealthSystem.h"

std::map<EntityHandle, Component*> HealthSystem::m_components;
bool HealthSystem::m_debug;

void HealthSystem::Init()
{
    m_debug = false;
}

void HealthSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void HealthSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void HealthSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        HealthComponent* pComponent = (HealthComponent*) it->second;
        if ( pComponent )
        {
            if ( pComponent->GetHealth() <= 0.0f )
            {
                pComponent->BeginDeath();
            }
        }
    }
}