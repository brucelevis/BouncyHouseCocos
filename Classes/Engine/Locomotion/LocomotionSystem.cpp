//
//  LocomotionSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/1/15.
//
//

#include "cocos2d.h"

#include "../Entity/EntitySystem.h"
#include "LocomotionComponent.h"
#include "LocomotionSystem.h"
#include "../Physics/PhysicsComponent.h"
#include "../Render/RenderComponent.h"
#include "../Render/RenderSystem.h"
#include "../../Game/Locomotion/LocomotionModes/RunLocomotionMode.h"

std::map<EntityHandle, Component*> LocomotionSystem::m_components;
LocomotionModeMap LocomotionSystem::m_locomotionModeTypes;
bool LocomotionSystem::m_debug;

void LocomotionSystem::Init()
{
    LocomotionModeRegister<RunLocomotionMode>( "RunLocomotionMode" );
    m_debug = false;
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
            PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( pComponent->m_entityHandle );
            if ( pPhysicsComponent )
            {
                float yVel = pPhysicsComponent->GetVelocity().y;
                JumpState pJumpState;
                if ( yVel > 0.5f )
                {
                    pJumpState = JumpState::JUMPING;
                }
                else if ( yVel < 0.5f )
                {
                    pJumpState = JumpState::FALLING;
                }
                else if ( yVel == 0.0f )
                {
                    pJumpState = JumpState::NOT_JUMPING;
                }
                
                if ( pJumpState == JumpState::FALLING && pComponent->m_jumpState == JumpState::JUMPING )
                {
                    cocos2d::EventCustom event( "VelocityApexReached" );
                    event.setUserData( &pComponent->m_entityHandle );
                    RenderSystem::m_activeScene->GetEventDispatcher()->dispatchEvent( &event );
                }
                
                pComponent->m_jumpState = pJumpState;
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