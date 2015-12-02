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
        pPhysicsComponent->ApplyImpulse( cocos2d::Vec2( 0.0f, 7000.0f ) );
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
    
//    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
//    if ( pPhysicsComponent )
//    {
//        cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
//        
//        
//        // ****** TODO: This is dirty and not a good way to make him run back and forth.  Rewrite this ASAP! ******* //
//        float xDir = 1.0f;
//        if ( pVelocity.x > 0.0f )
//        {
//            pFacing = RenderComponent::FacingDirection::RIGHT;
//            xDir = 1.0f;
//        }
//        else if ( pVelocity.x < 0.0f )
//        {
//            pFacing = RenderComponent::FacingDirection::LEFT;
//            xDir = -1.0f;
//        }
//        
//        float pImpulseAmount = ( pRunSpeed - fabs( pVelocity.x ) ) * xDir;
//        cocos2d::Vec2 pImpulse = cocos2d::Vec2( pImpulseAmount, 0.0f );
//        pPhysicsComponent->ApplyImpulse( pImpulse );
//    }
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        cocos2d::Vec2 pPosition = pPhysicsComponent->GetPosition() - pPhysicsComponent->GetOffset() + cocos2d::Vec2( m_runDir * ( pPhysicsComponent->GetWidth() * 0.5f - 1.0f ), 0.0f );
        cocos2d::Vec2 pEnd = pPosition + cocos2d::Vec2( m_runDir * 9.0f, 0.0f );
        cocos2d::Vec2 pHitPoint;
//        EntityHandle pEntityHandle = m_entityHandle;
//        CollisionCategory pCollisionMask = pPhysicsComponent->GetCollisionMask();
//        bool pHit = false;
//        cocos2d::PhysicsRayCastCallbackFunc pFunc = [&pPoint, &pHit, &pEntityHandle, &pCollisionMask](cocos2d::PhysicsWorld& i_world, const cocos2d::PhysicsRayCastInfo& i_info, void* i_data )->bool
//        {
//            if ( i_info.shape->getBody()->getNode()->getTag() != pEntityHandle && PhysicsSystem::IsInBitmask( pCollisionMask, (CollisionCategory) i_info.shape->getBody()->getCategoryBitmask() ) )
//            {
//                pPoint = i_info.contact;
//                pHit = true;
//            }
//            return true;
//        };
//        RenderSystem::m_activeScene->getPhysicsWorld()->rayCast( pFunc, pPosition, pEnd, nullptr );
        cocos2d::PhysicsRayCastInfo pInfo;
        bool pHit = pPhysicsComponent->RayCast( pPosition, pEnd, pInfo );
        if ( pHit )
        {
            m_runDir *= -1.0f;
        }
        
        cocos2d::Vec2 pVelocity = pPhysicsComponent->GetVelocity();
        float pImpulseAmount = ( pRunSpeed - fabs( pVelocity.x ) ) * m_runDir;
        cocos2d::Vec2 pImpulse = cocos2d::Vec2( pImpulseAmount, 0.0f );
        pPhysicsComponent->ApplyImpulse( pImpulse );
        
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
    }
    
    RenderComponent* pRenderComponent = EntitySystem::GetComponent<RenderComponent>( m_entityHandle );
    if ( pRenderComponent )
    {
        RenderComponent::FacingDirection pFacing = ( m_runDir == -1.0f ) ? RenderComponent::FacingDirection::LEFT : RenderComponent::FacingDirection::RIGHT;
        pRenderComponent->SetFacing( pFacing );
    }
}