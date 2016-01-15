//
//  MunitionSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "../Entity/EntitySystem.h"
#include "../Entity/DNASequencer.h"
#include "MunitionComponent.h"
#include "MunitionSystem.h"

MunitionSystem* MunitionSystem::s_instance;

MunitionSystem* MunitionSystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new MunitionSystem();
    }
    return s_instance;
}

void MunitionSystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void MunitionSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void MunitionSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void MunitionSystem::DNADataInit()
{

}

void MunitionSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        MunitionComponent* pComponent = (MunitionComponent*) it->second;
        if ( pComponent )
        {
            pComponent->Update( i_dt );
        }
    }
}

EntityHandle MunitionSystem::CreateMeleeMunition( EntityHandle i_ownerHandle, std::string i_dnaPath )
{
    Entity* pMunition = DNASequencer::CreateEntity( i_dnaPath );
    MunitionComponent* pMunitionComponent = EntitySystem::GetInstance()->GetComponent<MunitionComponent>( pMunition->m_entityHandle );
    if ( pMunitionComponent )
    {
        pMunitionComponent->MunitionActivate( i_ownerHandle );
    }
    
    return pMunition->m_entityHandle;
}

void MunitionSystem::DestroyMunition( EntityHandle i_entityHandle )
{
    EntitySystem::GetInstance()->MarkForDelete( i_entityHandle );
}