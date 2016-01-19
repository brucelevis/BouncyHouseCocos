//
//  StalactiteFallBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/18/16.
//
//

#include "StalactiteFallBrainState.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Event/EventManager.h"
#include "../../../../Engine/GroundDetect/GroundDetectComponent.h"
#include "../../../../Engine/Munition/MunitionSystem.h"
#include "../../../../Engine/Physics/PhysicsComponent.h"
#include "../../../Level/LevelSystem.h"

StalactiteFallBrainState::StalactiteFallBrainState()
{
    m_interruptible = true;
}

StalactiteFallBrainState::~StalactiteFallBrainState()
{
    
}

void StalactiteFallBrainState::Enter()
{
    
}

void StalactiteFallBrainState::Exit()
{
    
}

void StalactiteFallBrainState::OnActivate()
{
    m_active = true;
    
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "FALL" );    
    EventManager::GetInstance()->RegisterForEvent( "GroundChanged", CC_CALLBACK_1( StalactiteFallBrainState::OnGroundChangedEvent, this ), this );
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        pPhysicsComponent->GetPhysicsBody()->applyImpulse( cocos2d::Vec2( 0.0f, 1000.0f ) );
    }
    
    m_munitionHandle = MunitionSystem::GetInstance()->CreateMeleeMunition( m_entityHandle, "Baked/Munitions/icicle_fall.dna" );
}

void StalactiteFallBrainState::OnDeactivate()
{
    EventManager::GetInstance()->UnregisterForEvent( "GroundChanged", this );
    MunitionSystem::GetInstance()->DestroyMunition( m_munitionHandle );

    m_active = false;
}

void StalactiteFallBrainState::Update( float i_dt )
{
    
}

void StalactiteFallBrainState::OnGroundChangedEvent( cocos2d::EventCustom* i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetInstance()->GetComponent<GroundDetectComponent>( m_entityHandle );
        if ( pGroundDetectComponent )
        {
            if ( pGroundDetectComponent->GetOnGround() )
            {
                AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
                if ( pAIComponent )
                {
                    if ( pAIComponent->GetBrain() )
                    {
                        pAIComponent->GetBrain()->PopState();
                        pAIComponent->GetBrain()->PushState("StalactiteCrushBrainState");
                    }
                }
            }
        }
    }
}