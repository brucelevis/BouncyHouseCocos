//
//  RunLocomotionMode.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/2/15.
//
//

#include "AnimationComponent.h"
#include "EntitySystem.h"
#include "GroundDetectComponent.h"
#include "LocomotionComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "RunLocomotionMode.h"

void RunLocomotionMode::Init( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
}

void RunLocomotionMode::MoveToPoint( cocos2d::Vec2 i_point, float i_speed )
{
    
}

void RunLocomotionMode::Jump()
{
    GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetComponent<GroundDetectComponent>( m_entityHandle );
    if ( pGroundDetectComponent )
    {
        if ( !pGroundDetectComponent->GetOnGround() )
        {
            return;
        }
    }
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        pPhysicsComponent->ApplyImpulse( cocos2d::Vec2( 0.0f, 5000.0f ) );
        
        RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
        if ( pRenderComponent )
        {
            AnimationComponent* pAnimationComponent = EntitySystem::GetComponent<AnimationComponent>( m_entityHandle );
            if ( pAnimationComponent )
            {
                if ( pAnimationComponent->m_currentAnimation )
                {
                    pRenderComponent->m_sprite->stopAction( pAnimationComponent->m_currentAnimation );
                }
            }
            
            cocos2d::Vector<cocos2d::SpriteFrame*> pFrames( 18 );
            for ( int i = 0; i < 21; i++ )
            {
                char pFrameName[100] = {0};
                sprintf( pFrameName, "Vik1_Jump_%02d.png", i );
                pFrames.pushBack( cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName( pFrameName ) );
            }
            
            auto animation = cocos2d::Animation::createWithSpriteFrames( pFrames, 1.0f / 30.0f );
            auto animate = cocos2d::Animate::create( animation );
            pAnimationComponent->m_currentAnimation = pRenderComponent->m_sprite->runAction( animate );
        }
    }
}

void RunLocomotionMode::Update( float i_dt )
{
    float pRunSpeed = 0.0f;
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        pRunSpeed = pLocomotionComponent->GetRunSpeed();
    }
    
    RenderComponent::FacingDirection pFacing = RenderComponent::FacingDirection::NONE;
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        pFacing = pRenderComponent->GetFacing();
    }
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
        
        // ****** TODO: This is dirty and not a good way to make him run back and forth.  Rewrite this ASAP! ******* //
        float xDir = 1.0f;
        if ( pVelocity.x > 0.0f )
        {
            pFacing = RenderComponent::FacingDirection::RIGHT;
            xDir = 1.0f;
        }
        else if ( pVelocity.x < 0.0f )
        {
            pFacing = RenderComponent::FacingDirection::LEFT;
            xDir = -1.0f;
        }
        
        float pImpulseAmount = ( pRunSpeed - fabs( pVelocity.x ) ) * xDir;
        cocos2d::Vec2 pImpulse = cocos2d::Vec2( pImpulseAmount, 0.0f );
        pPhysicsComponent->ApplyImpulse( pImpulse );
    }
    
    if ( pRenderComponent )
    {
        pRenderComponent->SetFacing( pFacing );
    }
}