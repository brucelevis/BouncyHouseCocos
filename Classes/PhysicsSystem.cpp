//
//  PhysicsSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "EntitySystem.h"
#include "PhysicsSystem.h"
#include "PhysicsComponent.h"

std::map<EntityHandle, Component*> PhysicsSystem::m_components;

void PhysicsSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void PhysicsSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void PhysicsSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        PhysicsComponent* pComponent = (PhysicsComponent*) it->second;
        if ( pComponent && pComponent->m_physicsBody )
        {
            if ( pComponent->m_physicsBody->getPosition().y < 100.0f )
            {
                EntitySystem::MarkForDelete( pComponent->m_entityHandle );
                continue;
            }
        }
    }
}