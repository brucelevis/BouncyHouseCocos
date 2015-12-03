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
#include "LocomotionSystem.h"
#include "PhysicsComponent.h"
#include "PhysicsSystem.h"
#include "RenderComponent.h"
#include "RenderSystem.h"
#include "RunLocomotionMode.h"

void RunLocomotionMode::Init( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
    m_runDir = 1.0f;
}

void RunLocomotionMode::MoveToPoint( cocos2d::Vec2 i_point, float i_speed )
{
    
}

void RunLocomotionMode::Jump()
{
    bool pOnGround = false;
    GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetComponent<GroundDetectComponent>( m_entityHandle );
    if ( pGroundDetectComponent )
    {
        pOnGround = pGroundDetectComponent->GetOnGround();
        if ( !pOnGround && m_diving )
        {
            return;
        }
    }
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        if ( pOnGround )
        {
            pPhysicsComponent->ApplyImpulse( cocos2d::Vec2( 0.0f, 7000.0f ) );
        }
        else
        {
            pPhysicsComponent->ApplyImpulse( cocos2d::Vec2( 0.0f, -14000.0f ) );
            m_diving = true;
        }
    }
    
    AnimationComponent* pAnimationComponent = EntitySystem::GetComponent<AnimationComponent>( m_entityHandle );
    if ( pAnimationComponent )
    {
        pAnimationComponent->StartMotion( "Jump" );
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
    
    if ( m_diving )
    {
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetComponent<GroundDetectComponent>( m_entityHandle );
        if ( pGroundDetectComponent )
        {
            if ( pGroundDetectComponent->GetOnGround() )
            {
                m_diving = false;
            }
        }
    }
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        cocos2d::Vec2 pPosition;
        cocos2d::Vec2 pEnd;
        cocos2d::Vec2 pHitPoint;
        cocos2d::PhysicsRayCastInfo pInfo;
        bool pHit = false;
        
        for ( int i = -1; i <= 1; i++ )
        {
            float pOffset = ((float) i) * 0.33f * pPhysicsComponent->GetHeight();
            pPosition = pPhysicsComponent->GetPosition() - pPhysicsComponent->GetOffset() + cocos2d::Vec2( m_runDir * ( pPhysicsComponent->GetWidth() * 0.5f - 1.0f ), pPhysicsComponent->GetHeight() * 0.5f + pOffset );
            pEnd = pPosition + cocos2d::Vec2( m_runDir * 9.0f, 0.0f );
            
            pHit = pPhysicsComponent->RayCast( pPosition, pEnd, pInfo );
            
#ifdef DEBUG
            if ( LocomotionSystem::m_debug )
            {
                cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
                pDrawNode->drawSegment( pPosition, pEnd, 1, cocos2d::Color4F::RED );
                if ( pHit )
                {
                    pDrawNode->drawPoint( pHitPoint, 3.0f, cocos2d::Color4F::GREEN );
                }
                RenderSystem::DebugDraw( pDrawNode, 0.0001f );
            }
#endif
            
            if ( pHit )
            {
                pHitPoint = pInfo.contact;
                break;
            }
        }

        if ( pHit )
        {
            cocos2d::Vec2 pRayDir = cocos2d::Vec2( pEnd - pPosition );
            pRayDir.normalize();
            
            if ( pInfo.normal.dot( pRayDir ) >= 0.75f )
            {
                m_runDir *= -1.0f;
            }

        }
    
        cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
        float pImpulseAmount = ( pRunSpeed - fabs( pVelocity.x ) ) * m_runDir;
        cocos2d::Vec2 pImpulse = cocos2d::Vec2( pImpulseAmount, 0.0f );
        pPhysicsComponent->ApplyImpulse( pImpulse );
    }
    
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        RenderComponent::FacingDirection pFacing = ( m_runDir == -1.0f ) ? RenderComponent::FacingDirection::LEFT : RenderComponent::FacingDirection::RIGHT;
        pRenderComponent->SetFacing( pFacing );
    }
}