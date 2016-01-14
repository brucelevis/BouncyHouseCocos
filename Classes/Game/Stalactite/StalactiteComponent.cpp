//
//  StalactiteComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/9/16.
//
//

#include "StalactiteComponent.h"
#include "../../Engine/Animation/AnimationComponent.h"
#include "../../Engine/GroundDetect/GroundDetectComponent.h"
#include "../../Engine/Health/HealthComponent.h"
#include "../../Engine/Physics/PhysicsComponent.h"
#include "../../Engine/Entity/EntitySystem.h"
#include "../../Engine/Render/RenderSystem.h"

std::string StalactiteComponent::s_componentType = "StalactiteComponent";

void StalactiteComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
}

void StalactiteComponent::OnActivate()
{
    m_timer = 3.0f;
    m_wiggling = true;
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        pPhysicsComponent->GetPhysicsBody()->setVelocityLimit( 0.0f );
    }
    
    cocos2d::EventListenerCustom* pGroundChangedListener = cocos2d::EventListenerCustom::create( "GroundChanged", CC_CALLBACK_1( StalactiteComponent::OnGroundChangedEvent, this ) );
    RenderSystem::m_activeScene->GetEventDispatcher()->addEventListenerWithFixedPriority( pGroundChangedListener, 1 );
}

StalactiteComponent::~StalactiteComponent()
{
    
}

void StalactiteComponent::Update( float i_dt )
{
    m_timer -= i_dt;
    if ( m_timer <= 0.0f && m_wiggling )
    {
        PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
        if ( pPhysicsComponent )
        {
            pPhysicsComponent->GetPhysicsBody()->setVelocityLimit( 10000.0f );
            pPhysicsComponent->GetPhysicsBody()->applyImpulse( cocos2d::Vec2( 0.0f, 1000.0f ) );
        } 
        m_wiggling = false;
        m_timer = 3.0f;
    }
    if ( m_timer <= 0.0f && !m_wiggling )
    {
        HealthComponent* pHealthComponent = EntitySystem::GetComponent<HealthComponent>( m_entityHandle );
        if ( pHealthComponent )
        {
            pHealthComponent->ChangeHealth( -999999.0f );
        }
    }
}

void StalactiteComponent::OnGroundChangedEvent( cocos2d::EventCustom* i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( m_entityHandle == pEntityHandle )
    {
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetComponent<GroundDetectComponent>( m_entityHandle );
        if ( pGroundDetectComponent )
        {
            if ( pGroundDetectComponent->GetOnGround() )
            {
                AnimationComponent* pAnimationComponent = EntitySystem::GetComponent<AnimationComponent>( m_entityHandle );
                if ( pAnimationComponent )
                {
                    pAnimationComponent->StartMotion( "Crush" );
                }
            }
        }
    }
}