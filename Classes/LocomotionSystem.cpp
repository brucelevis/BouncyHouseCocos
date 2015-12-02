//
//  LocomotionSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/1/15.
//
//

#include "EntitySystem.h"
#include "LocomotionComponent.h"
#include "LocomotionSystem.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "RunLocomotionMode.h"

std::map<EntityHandle, Component*> LocomotionSystem::m_components;
LocomotionModeMap LocomotionSystem::m_locomotionModeTypes;

void LocomotionSystem::Init()
{
    LocomotionModeRegister<RunLocomotionMode>( "RunLocomotionMode" );
}

void LocomotionSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void LocomotionSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void LocomotionSystem::Update( float i_dt )
{
    for ( std::map<EntityHandle, Component*>::iterator it = m_components.begin(); it != m_components.end(); it++ )
    {
        LocomotionComponent* pComponent = (LocomotionComponent*) it->second;
        if ( pComponent )
        {
            if ( pComponent->m_locomotionMode )
            {
                pComponent->m_locomotionMode->Update( i_dt );
            }          
        }
    }
}

LocomotionMode* LocomotionSystem::CreateLocomotionMode( std::string i_locomotionModeType )
{
    LocomotionModeMap::iterator it = m_locomotionModeTypes.find( i_locomotionModeType );
    if ( it == LocomotionSystem::m_locomotionModeTypes.end() )
        return NULL;
    
    LocomotionMode* pLocomotionMode = it->second();
    return pLocomotionMode;
}