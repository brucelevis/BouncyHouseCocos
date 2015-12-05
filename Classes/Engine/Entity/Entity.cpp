//
//  Entity.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "Entity.h"

void Entity::AddComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->s_componentType, i_component ) );
}

void Entity::RemoveComponent( Component* i_component )
{
    m_components.erase( i_component->s_componentType );
}