//
//  StalactiteWiggleBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/18/16.
//
//

#include "StalactiteWiggleBrainState.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Physics/PhysicsComponent.h"
#include "../../../Level/LevelSystem.h"

StalactiteWiggleBrainState::StalactiteWiggleBrainState()
{
    m_interruptible = true;
}

StalactiteWiggleBrainState::~StalactiteWiggleBrainState()
{
    
}

void StalactiteWiggleBrainState::Enter()
{
    m_timer = 3.0f;
}

void StalactiteWiggleBrainState::Exit()
{
    
}

void StalactiteWiggleBrainState::OnActivate()
{
    m_active = true;
    
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "WIGGLE" );
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        pPhysicsComponent->GetPhysicsBody()->setVelocityLimit( 0.0f );
    }
}

void StalactiteWiggleBrainState::OnDeactivate()
{
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        pPhysicsComponent->GetPhysicsBody()->setVelocityLimit( 1000000.0f );
    }
    
    m_active = false;
}

void StalactiteWiggleBrainState::Update( float i_dt )
{
    m_timer -= i_dt;
    if ( m_timer <= 0.0f )
    {
        AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
        if ( pAIComponent )
        {
            if ( pAIComponent->GetBrain() )
            {
                pAIComponent->GetBrain()->PopState();
                pAIComponent->GetBrain()->PushState("StalactiteFallBrainState");
            }
        }
    }
}