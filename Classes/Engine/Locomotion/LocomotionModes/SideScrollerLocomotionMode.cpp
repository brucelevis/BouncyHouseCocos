//
//  SideScrollerLocomotionMode.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "SideScrollerLocomotionMode.h"
#include "../../Entity/EntitySystem.h"
#include "../../Event/EventManager.h"
#include "../../GroundDetect/GroundDetectComponent.h"
#include "../LocomotionComponent.h"
#include "../../Physics/PhysicsComponent.h"
#include "../../Render/RenderComponent.h"

void SideScrollerLocomotionMode::Init( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
}

void SideScrollerLocomotionMode::MoveAtSpeed( cocos2d::Vec2 i_moveDir, float i_speed )
{
    float pRunSpeed = i_speed;
    if ( pRunSpeed < 0.0f)
    {
        LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
        if ( pLocomotionComponent )
        {
            pRunSpeed = pLocomotionComponent->GetRunSpeed();
        }
    }
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        float pImpulseAmount;
        cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
        float pCurrentDir = pVelocity.x > 0.0f ? 1.0f : -1.0f;
        if ( pCurrentDir == i_moveDir.x )
        {
            float pCurrentSpeed = fabs( pVelocity.x ) <= pRunSpeed ? fabs( pVelocity.x ) : pRunSpeed;
            pImpulseAmount = ( pRunSpeed - pCurrentSpeed ) * i_moveDir.x;
        }
        else
        {
            pImpulseAmount = pRunSpeed * i_moveDir.x;
        }
        ASSERTS( fabs( pImpulseAmount ) <= pRunSpeed, "Impulse is too fast!" );
        cocos2d::Vec2 pImpulse = cocos2d::Vec2( pImpulseAmount, 0.0f );
        pPhysicsComponent->ApplyImpulse( pImpulse );
        
        PhysicsComponent::FacingDirection pFacing = ( i_moveDir.x == -1.0f ) ? PhysicsComponent::FacingDirection::LEFT : PhysicsComponent::FacingDirection::RIGHT;
        pPhysicsComponent->SetFacing( pFacing );
        
        ASSERTS( pPhysicsComponent->GetFacing() == pFacing, "Sprite facing wrong way!" );

    }
}

void SideScrollerLocomotionMode::Update( float i_dt )
{
    
}
