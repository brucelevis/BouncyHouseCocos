//
//  DiveBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "DiveBrainState.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Event/EventManager.h"
#include "../../../../Engine/GroundDetect/GroundDetectComponent.h"
#include "../../../../Engine/Locomotion/LocomotionComponent.h"
#include "../../../../Engine/Locomotion/LocomotionSystem.h"
#include "../../../../Engine/Munition/MunitionSystem.h"
#include "../../../../Engine/Physics/PhysicsComponent.h"
#include "../../../../Engine/Render/DebugDrawSystem.h"

DiveBrainState::DiveBrainState()
{
    m_runDir = -1.0f;
    m_interruptible = false;
}

DiveBrainState::~DiveBrainState()
{
    
}

void DiveBrainState::Enter()
{
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        m_runDir = pPhysicsComponent->GetVelocity().x > 0.0f ? 1.0f : -1.0f;
    }
    
    cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
    pVelocity.y = 0.0f;
    pPhysicsComponent->SetVelocity( pVelocity );
    
    pPhysicsComponent->ApplyImpulse( cocos2d::Vec2( 0.0f, -5000.0f * pPhysicsComponent->GetMass() ) );
    
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "DIVE" );
}

void DiveBrainState::Exit()
{
    
}

void DiveBrainState::OnActivate()
{
    m_active = true;
    EventManager::GetInstance()->RegisterForEvent( "GroundChanged", CC_CALLBACK_1( DiveBrainState::OnGroundChangedEvent, this ), this );
    EventManager::GetInstance()->RegisterForEvent( "MunitionContact", CC_CALLBACK_1( DiveBrainState::OnMunitionContactEvent, this ), this );
    
    
    m_munitionHandle = MunitionSystem::GetInstance()->CreateMeleeMunition( m_entityHandle, "Baked/Munitions/player_dive.dna" );
    
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetLocomotionMode( "SideScrollerLocomotionMode" );
    }
}

void DiveBrainState::OnDeactivate()
{
    m_active = false;
    EventManager::GetInstance()->UnregisterForEvent( "GroundChanged", this );
    EventManager::GetInstance()->UnregisterForEvent( "MunitionContact", this );
    
    MunitionSystem::GetInstance()->DestroyMunition( m_munitionHandle );
    
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetLocomotionMode( "" );
    }
}

void DiveBrainState::OnGroundChangedEvent( cocos2d::EventCustom *i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetInstance()->GetComponent<GroundDetectComponent>( m_entityHandle );
        ASSERTS( pGroundDetectComponent && pGroundDetectComponent->GetOnGround(), "How come we're not on the ground?" );
        if ( pGroundDetectComponent && pGroundDetectComponent->GetOnGround() )
        {
            AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
            if ( pAIComponent )
            {
                if ( pAIComponent->GetBrain() )
                {
                     pAIComponent->GetBrain()->PopState();
                }
            }
        }
    }
}

void DiveBrainState::OnMunitionContactEvent( cocos2d::EventCustom *i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
        if ( pAIComponent )
        {
            if ( pAIComponent->GetBrain() )
            {
                AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "SMASH" );
                
                pAIComponent->GetBrain()->PopState();
                pAIComponent->GetBrain()->PushState( "JumpBrainState" );
            }
        }
    }
}
