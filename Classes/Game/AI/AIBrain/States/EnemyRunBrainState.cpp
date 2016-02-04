//
//  EnemyRunBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "EnemyRunBrainState.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/GroundDetect/GroundDetectComponent.h"
#include "../../../Level/LevelSystem.h"

void EnemyRunBrainState::Update( float i_dt )
{
    Entity* pPlayer = LevelSystem::GetInstance()->GetLevel()->GetPlayer();
    if ( pPlayer )
    {
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetInstance()->GetComponent<GroundDetectComponent>( m_entityHandle );
        if ( pGroundDetectComponent && pGroundDetectComponent->GetOnGround() )
        {
            float pDistanceToPlayerSquared = GetDistanceToEntitySquared( pPlayer->m_entityHandle );
            if ( pDistanceToPlayerSquared <= 20000.0f )
            {
                AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
                if ( pAIComponent )
                {
                    if ( pAIComponent->GetBrain() )
                    {
                        pAIComponent->GetBrain()->PushState( "EnemyBraceBrainState" );
                        return;
                    }
                }
            }
        }
    }
    RunBrainState::Update( i_dt );
}