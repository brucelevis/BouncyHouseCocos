//
//  RunBrainState.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "RunBrainState.h"
#include "../../../../Engine/AI/AIComponent.h"
#include "../../../../Engine/Animation/AnimationSystem.h"
#include "../../../../Engine/Entity/EntitySystem.h"
#include "../../../../Engine/Event/EventManager.h"
#include "../../../../Engine/Locomotion/LocomotionComponent.h"
#include "../../../../Engine/Locomotion/LocomotionSystem.h"
#include "../../../../Engine/Physics/PhysicsComponent.h"
#include "../../../../Engine/Render/DebugDrawSystem.h"

RunBrainState::RunBrainState()
{
    m_runDir = -1.0f;
}

RunBrainState::~RunBrainState()
{

}

void RunBrainState::Enter()
{
    
}

void RunBrainState::Exit()
{

}

void RunBrainState::OnActivate()
{
    m_active = true;
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetLocomotionMode( "SideScrollerLocomotionMode" );
    }
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        m_runDir = pPhysicsComponent->GetVelocity().x > 0.0f ? 1.0f : -1.0f;
    }
    
    EventManager::GetInstance()->RegisterForEvent( "AvatarAction_Jump", CC_CALLBACK_1( RunBrainState::OnAvatarAction_Jump, this ), this );
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "RUN" );
}

void RunBrainState::OnDeactivate()
{
    m_active = false;
    EventManager::GetInstance()->UnregisterForEvent( "AvatarAction_Jump", this );
    
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        pLocomotionComponent->SetLocomotionMode( "" );
    }
}

void RunBrainState::Update( float i_dt )
{
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
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
            pPosition = pPhysicsComponent->GetPosition() - pPhysicsComponent->GetOffset() + ( cocos2d::Vec2( m_runDir * ( pPhysicsComponent->GetWidth() * fabs( pPhysicsComponent->GetNode()->getScaleX() ) * 0.5f - 1.0f ), pPhysicsComponent->GetHeight() * fabs( pPhysicsComponent->GetNode()->getScaleY() ) * 0.5f + pOffset ) );
            pEnd = pPosition + cocos2d::Vec2( m_runDir * 9.0f, 0.0f );
            
            pHit = pPhysicsComponent->RayCast( pPosition, pEnd, pInfo );
            
#ifdef DEBUG
            if ( LocomotionSystem::GetInstance()->GetDebug() )
            {
                cocos2d::DrawNode* pDrawNode = cocos2d::DrawNode::create();
                pDrawNode->drawSegment( pPosition, pEnd, 1, cocos2d::Color4F::RED );
                if ( pHit )
                {
                    pDrawNode->drawPoint( pHitPoint, 3.0f, cocos2d::Color4F::GREEN );
                }
                DebugDrawSystem::GetInstance()->DebugDraw( pDrawNode, 0.0001f );
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
            float pSideDot = pInfo.normal.dot( cocos2d::Vec2( m_runDir, 0.0f ) );
            if ( pSideDot <= -0.75f )
            {
                if ( pInfo.normal.x > 0.0f )
                {
                    m_runDir = 1.0f;
                }
                else
                {
                    m_runDir = -1.0f;
                }
            }
        }
    }
    LocomotionComponent* pLocomotionComponent = EntitySystem::GetInstance()->GetComponent<LocomotionComponent>( m_entityHandle );
    if ( pLocomotionComponent )
    {
        if ( pLocomotionComponent->m_locomotionMode )
        {
            pLocomotionComponent->m_locomotionMode->MoveAtSpeed( cocos2d::Vec2( m_runDir, 0.0f ) );
        }
    }
}

void RunBrainState::OnAvatarAction_Jump( cocos2d::EventCustom *i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( m_entityHandle );
        if ( pAIComponent )
        {
            if ( pAIComponent->GetBrain() )
            {
                pAIComponent->GetBrain()->PushState( "JumpBrainState" );
            }
        }
    }
}