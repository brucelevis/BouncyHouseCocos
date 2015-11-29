//
//  EntitySystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//
#include <vector>

#include "EntitySystem.h"
#include "RenderComponent.h"

std::vector<EntityHandle> EntitySystem::m_markedForDelete;
std::map<EntityHandle, Entity*> EntitySystem::m_entities;

Entity* EntitySystem::CreateEntity()
{
    EntityHandle newHandle = rand() % 1000000000;
    while ( EntitySystem::m_entities.count( newHandle ) != 0 )
        newHandle = rand() % 1000000000;
    
    Entity* pEntity = new Entity();
    pEntity->m_entityHandle = newHandle;
    
    EntitySystem::m_entities.insert( std::make_pair( pEntity->m_entityHandle, pEntity ) );
    
    return pEntity;
}

void EntitySystem::MarkForDelete( EntityHandle i_entityHandle )
{
    m_markedForDelete.push_back( i_entityHandle );
}

void EntitySystem::RemoveEntity( EntityHandle i_entityHandle )
{
    Entity* pEntity = EntitySystem::GetEntity( i_entityHandle );
    
    if ( pEntity )
    {
        for ( std::map<std::string, Component*>::iterator it = pEntity->m_components.begin(); it != pEntity->m_components.end(); it++ )
        {
            Component* pComponent = it->second;
            if (pComponent )
                delete pComponent;
        }
        
        delete pEntity;
    }
    EntitySystem::m_entities.erase( i_entityHandle );
}

Entity* EntitySystem::GetEntity( EntityHandle i_entityHandle )
{
    if ( EntitySystem::m_entities.find( i_entityHandle ) != EntitySystem::m_entities.end() )
        return EntitySystem::m_entities.at( i_entityHandle );
    else
        return NULL;
}

void EntitySystem::Update( float i_dt )
{
    if ( m_markedForDelete.size() > 0 )
    {
        for ( int i = 0; i < m_markedForDelete.size(); i++ )
        {
            RemoveEntity( m_markedForDelete[i] );
        }
        m_markedForDelete.clear();
    }
}