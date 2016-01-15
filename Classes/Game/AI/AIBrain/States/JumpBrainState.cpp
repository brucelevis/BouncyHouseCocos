//
//  JumpBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "JumpBrainState.h"
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

JumpBrainState::JumpBrainState()
{
    m_runDir = -1.0f;
}

JumpBrainState::~JumpBrainState()
{
    
}

void JumpBrainState::Enter()
{
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetLocomotionMode( "SideScrollerLocomotionMode" );
    }
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        m_runDir = pPhysicsComponent->GetVelocity().x > 0.0f ? 1.0f : -1.0f;
    }
    
    cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
    pVelocity.y = 0.0f;
    pPhysicsComponent->SetVelocity( pVelocity );
    pPhysicsComponent->ApplyImpulse( cocos2d::Vec2( 0.0f, JUMP_VELOCITY ) );
    
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "JUMP" );
}

void JumpBrainState::Exit()
{
    
}

void JumpBrainState::OnActivate()
{
    m_active = true;
    EventManager::GetInstance()->RegisterForEvent( "GroundChanged", CC_CALLBACK_1( JumpBrainState::OnGroundChangedEvent, this ), this );
    EventManager::GetInstance()->RegisterForEvent( "AvatarAction_Jump", CC_CALLBACK_1( JumpBrainState::OnAvatarAction_Jump, this ), this );
    EventManager::GetInstance()->RegisterForEvent( "MunitionContact", CC_CALLBACK_1( JumpBrainState::OnMunitionContactEvent, this ), this );
    
    m_munitionHandle = MunitionSystem::GetInstance()->CreateMeleeMunition( m_entityHandle, "Baked/Munitions/player_dive.dna" );
}

void JumpBrainState::OnDeactivate()
{
    m_active = false;
    EventManager::GetInstance()->UnregisterForEvent( "GroundChanged", this );
    EventManager::GetInstance()->UnregisterForEvent( "AvatarAction_Jump", this );
    EventManager::GetInstance()->UnregisterForEvent( "MunitionContact", this );
    
    MunitionSystem::GetInstance()->DestroyMunition( m_munitionHandle );
}

void JumpBrainState::OnGroundChangedEvent( cocos2d::EventCustom *i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetInstance()->GetComponent<GroundDetectComponent>( m_entityHandle );
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

void JumpBrainState::OnAvatarAction_Jump( cocos2d::EventCustom *i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
        if ( pAIComponent )
        {
            if ( pAIComponent->GetBrain() )
            {
                pAIComponent->GetBrain()->PopState();
                pAIComponent->GetBrain()->PushState( "DiveBrainState" );
            }
        }
    }
}

void JumpBrainState::OnMunitionContactEvent( cocos2d::EventCustom *i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
        if ( pAIComponent )
        {
            if ( pAIComponent->GetBrain() )
            {
                pAIComponent->GetBrain()->PopState();
                pAIComponent->GetBrain()->PushState( "JumpBrainState" );
            }
        }
    }
}
