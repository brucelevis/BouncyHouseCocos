//
//  AIBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "AIBrainState.h"
#include "../../../Entity/EntitySystem.h"
#include "../../../Physics/PhysicsComponent.h"

float AIBrainState::GetDistanceToEntitySquared( EntityHandle i_entityHandle )
{
    cocos2d::Vec2 pPos;
    cocos2d::Vec2 pOtherPos;
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( i_entityHandle );
    if ( pPhysicsComponent )
    {
        pOtherPos = pPhysicsComponent->GetPosition();
    }
    PhysicsComponent* pOtherPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pOtherPhysicsComponent )
    {
        pPos = pOtherPhysicsComponent->GetPosition();
    }
    
    cocos2d::Vec2 pDiff = pOtherPos - pPos;
    
    return pDiff.lengthSquared();
}

cocos2d::Vec2 AIBrainState::GetDirectionToEntity( EntityHandle i_entityHandle )
{
    cocos2d::Vec2 pPos;
    cocos2d::Vec2 pOtherPos;
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( i_entityHandle );
    if ( pPhysicsComponent )
    {
        pOtherPos = pPhysicsComponent->GetPosition();
    }
    PhysicsComponent* pOtherPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pOtherPhysicsComponent )
    {
        pPos = pOtherPhysicsComponent->GetPosition();
    }
    
    cocos2d::Vec2 pDiff = pOtherPos - pPos;
    pDiff.normalize();
    return pDiff;
}