//
//  EnemyBraceBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "EnemyBraceBrainState.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Munition/MunitionSystem.h"
#include "../../../../Engine/Render/RenderComponent.h"
#include "../../../Level/LevelSystem.h"

EnemyBraceBrainState::EnemyBraceBrainState()
{
    m_interruptible = true;
}

EnemyBraceBrainState::~EnemyBraceBrainState()
{
    
}

void EnemyBraceBrainState::Enter()
{
    
}

void EnemyBraceBrainState::Exit()
{
    
}

void EnemyBraceBrainState::OnActivate()
{
    m_active = true;
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "IDLE" );
    
    m_munitionHandle = MunitionSystem::GetInstance()->CreateMeleeMunition( m_entityHandle, "Baked/Munitions/enemy_brace.dna" );
}

void EnemyBraceBrainState::OnDeactivate()
{
    m_active = false;
    
    MunitionSystem::GetInstance()->DestroyMunition( m_munitionHandle );
}

void EnemyBraceBrainState::Update( float i_dt )
{
    Entity* pPlayer = LevelSystem::GetInstance()->GetLevel()->GetPlayer();
    if ( pPlayer )
    {
        float pDistanceToPlayerSquared = GetDistanceToEntitySquared( pPlayer->m_entityHandle );
        if ( pDistanceToPlayerSquared >= 120000.0f )
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
        else
        {
            RenderComponent* pRenderComponent = EntitySystem::GetInstance()->GetComponent<RenderComponent>( m_entityHandle );
            if ( pRenderComponent )
            {
                cocos2d::Vec2 pDirectionToPlayer = GetDirectionToEntity( pPlayer->m_entityHandle );
                if ( pDirectionToPlayer.x > 0.0f )
                {
                    pRenderComponent->SetFacing( RenderComponent::FacingDirection::RIGHT );
                }
                else if ( pDirectionToPlayer.x < 0.0f )
                {
                    pRenderComponent->SetFacing( RenderComponent::FacingDirection::LEFT );
                }
            }
        }
    }
}
