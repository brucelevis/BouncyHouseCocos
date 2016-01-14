//
//  StalactiteComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/9/16.
//
//

#include "StalactiteComponent.h"
#include "../../Engine/Animation/AnimationSystem.h"
#include "../../Engine/Event/EventManager.h"
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
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        pPhysicsComponent->GetPhysicsBody()->setVelocityLimit( 0.0f );
    }

    EventManager::GetInstance()->RegisterForEvent( "GroundChanged", CC_CALLBACK_1( StalactiteComponent::OnGroundChangedEvent, this ), this );
}

StalactiteComponent::~StalactiteComponent()
{
    EventManager::GetInstance()->UnregisterForEvent( "GroundChanged", this );
}

void StalactiteComponent::Update( float i_dt )
{
    m_timer -= i_dt;
    if ( m_timer <= 0.0f && m_wiggling )
    {
        PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
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
        HealthComponent* pHealthComponent = EntitySystem::GetInstance()->GetComponent<HealthComponent>( m_entityHandle );
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
        GroundDetectComponent* pGroundDetectComponent = EntitySystem::GetInstance()->GetComponent<GroundDetectComponent>( m_entityHandle );
        if ( pGroundDetectComponent )
        {
            if ( pGroundDetectComponent->GetOnGround() )
            {
                BeginCrush();
            }
        }
    }
}

void StalactiteComponent::BeginCrush()
{
    AnimationSystem::GetInstance()->SendEvent( m_entityHandle, "CRUSH" );
    
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        pPhysicsComponent->SetCategoryMask( CollisionCategory::Environment );
        pPhysicsComponent->SetCollisionMask( CollisionCategory::Environment );
        pPhysicsComponent->SetContactMask( CollisionCategory::Environment );
    }
}