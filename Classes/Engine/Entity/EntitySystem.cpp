//
//  EntitySystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//
#include "ComponentSystem.h"
#include "../../DEFINES.h"
#include "EntitySystem.h"
#include "../Event/EventManager.h"

EntitySystem* EntitySystem::s_instance;

EntitySystem* EntitySystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new EntitySystem();
    }
    return s_instance;
}

void EntitySystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}
Entity* EntitySystem::CreateEntity()
{
    EntityHandle newHandle = rand() % 10000;
    ASSERTS( EntitySystem::m_entities.size() < 10000, "Entity count exceeds number of EntityHandles" );
    while ( EntitySystem::m_entities.count( newHandle ) != 0 )
        newHandle = rand() % 10000;
    
    Entity* pEntity = new Entity();
    pEntity->m_entityHandle = newHandle;
    
    EntitySystem::m_entities.insert( std::make_pair( pEntity->m_entityHandle, pEntity ) );
    
    return pEntity;
}

Component* EntitySystem::AttachAndInitComponent( EntityHandle i_entityHandle, std::string i_componentType, const rapidjson::Value& i_dnaObject )
{
    Component* pComponent = AttachComponent( i_entityHandle, i_componentType );
    if ( pComponent )
    {
        pComponent->DNADataInit( i_entityHandle, i_dnaObject );
    }
    return pComponent;
}

Component* EntitySystem::AttachComponent( EntityHandle i_entityHandle, std::string i_componentType )
{
    Entity* pEntity = EntitySystem::GetEntity( i_entityHandle );
    Component* pComponent = ComponentSystem::CreateComponent( i_componentType );
    ASSERTS( pComponent, "Newly created component is null!" );
    if ( pComponent )
    {
        pComponent->Init( i_entityHandle );
        pEntity->m_components.insert( std::make_pair( i_componentType, pComponent ) );
    }
    return pComponent;
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
        EventManager::GetInstance()->SendEvent( "RemovingEntity", (void*) &i_entityHandle );
        
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
    for ( std::map<EntityHandle, Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); it++ )
    {
        Entity* pEntity = it->second;
        if ( pEntity )
        {
            for ( std::map<std::string, Component*>::iterator cIt = pEntity->m_components.begin(); cIt != pEntity->m_components.end(); cIt++ )
            {
                Component* pComponent = cIt->second;
                if (pComponent )
                {
                    pComponent->Update( i_dt );
                }
            }
        }
    }

    if ( m_markedForDelete.size() > 0 )
    {
        for ( int i = 0; i < m_markedForDelete.size(); i++ )
        {
            RemoveEntity( m_markedForDelete[i] );
        }
        m_markedForDelete.clear();
    }
}

#ifdef DEBUG
std::string EntitySystem::GetNameDoNotUseInCode( EntityHandle i_entityHandle )
{
    Entity* pEntity = EntitySystem::GetInstance()->GetEntity( i_entityHandle );
    if ( pEntity )
    {
        return pEntity->GetName();
    }
    
    return std::string( "NULL Entity" );
}
#endif
