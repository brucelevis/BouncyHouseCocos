//
//  StunBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "StunBrainState.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../Level/LevelSystem.h"

StunBrainState::StunBrainState()
{
    m_interruptible = false;
}

StunBrainState::~StunBrainState()
{
    
}

void StunBrainState::Enter()
{
    m_timer = 2.0f;
}

void StunBrainState::Exit()
{
    
}

void StunBrainState::OnActivate()
{
    m_active = true;
    
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "IDLE" );
}

void StunBrainState::OnDeactivate()
{
    m_active = false;
}

void StunBrainState::Update( float i_dt )
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
            }
        }
    }
}
