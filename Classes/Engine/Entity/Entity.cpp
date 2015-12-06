//
//  Entity.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "Entity.h"

Entity::~Entity()
{
    for ( std::map<std::string, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        Component* pComponent = it->second;
        if (pComponent )
        {
            pComponent->Deactivate();
            delete pComponent;
        }
    }
}

void Entity::AddComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->s_componentType, i_component ) );
}

void Entity::RemoveComponent( Component* i_component )
{
    m_components.erase( i_component->s_componentType );
}