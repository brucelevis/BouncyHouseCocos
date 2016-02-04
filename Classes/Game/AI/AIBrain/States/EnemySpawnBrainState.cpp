//
//  EnemySpawnState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 2/3/16.
//
//

#include "EnemySpawnBrainState.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Render/RenderComponent.h"

EnemySpawnBrainState::EnemySpawnBrainState()
{
    m_interruptible = true;
}

EnemySpawnBrainState::~EnemySpawnBrainState()
{
    
}

void EnemySpawnBrainState::Enter()
{
    
}

void EnemySpawnBrainState::Exit()
{
    
}

void EnemySpawnBrainState::OnActivate()
{
    m_active = true;
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "IDLE" );
    
    m_fadeTimer = 0.5f;
    auto fadeIn = cocos2d::FadeIn::create( m_fadeTimer );
    RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        pRenderComponent->m_sprite->setOpacity( 0 );
        pRenderComponent->m_sprite->runAction( fadeIn );
    }
}

void EnemySpawnBrainState::OnDeactivate()
{
    m_active = false;
}

void EnemySpawnBrainState::Update( float i_dt )
{
    m_fadeTimer -= i_dt;
    if ( m_fadeTimer <= 0.0f )
    {
        AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
        if ( pAIComponent )
        {
            if ( pAIComponent->GetBrain() )
            {
                pAIComponent->GetBrain()->PopState();
                pAIComponent->GetBrain()->PushState( "EnemyRunBrainState" );
            }
        }
    }
}
