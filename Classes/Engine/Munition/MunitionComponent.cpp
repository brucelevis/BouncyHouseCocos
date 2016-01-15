//
//  MunitionComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "MunitionComponent.h"
#include "cocos2d.h"

#include "../Entity/EntitySystem.h"
#include "../Event/EventManager.h"
#include "../Health/HealthComponent.h"
#include "MunitionSystem.h"
#include "../Physics/PhysicsComponent.h"

std::string MunitionComponent::s_componentType = "MunitionComponent";

void MunitionComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    m_ownerHandle = -1;
    MunitionSystem::GetInstance()->RegisterComponent( this );
    
    if ( i_dnaObject.HasMember( "Damage" ) )
    {
        m_damage = i_dnaObject["Damage"].GetDouble();
    }
}

void MunitionComponent::OnActivate()
{
    EventManager::GetInstance()->RegisterForEvent( "PhysicsContactBegin", CC_CALLBACK_1( MunitionComponent::OnPhysicsContactBeginEvent, this ), this );
}

void MunitionComponent::OnDeactivate()
{
    EventManager::GetInstance()->UnregisterForEvent( "PhysicsContactBegin", this );
}

MunitionComponent::~MunitionComponent()
{
    MunitionSystem::GetInstance()->UnregisterComponent( this );
}

void MunitionComponent::Update( float i_dt )
{
//    PhysicsComponent* pOPC = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_ownerHandle );
//    if ( pOPC )
//    {
//        PhysicsComponent* pPC = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
//        if ( pPC )
//        {
//            pPC->SetPosition( pOPC->GetPosition() );
//        }
//    }
}

void MunitionComponent::MunitionActivate( EntityHandle i_ownerHandle )
{
    m_ownerHandle = i_ownerHandle;
    
    PhysicsComponent* pOPC = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_ownerHandle );
    if ( pOPC )
    {
        PhysicsComponent* pPC = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
        if ( pPC )
        {
            pPC->GetNode()->removeFromParentAndCleanup( false );
            pOPC->GetNode()->addChild( pPC->GetNode() );
            pPC->SetPosition( cocos2d::Vec2( pOPC->GetNode()->getContentSize().width * 0.5f, 0.0f ) );
        }
    }
}

void MunitionComponent::MunitionDeactivate()
{
    
}

void MunitionComponent::OnPhysicsContactBeginEvent( cocos2d::EventCustom* i_event )
{
    PhysicsContactInfo* pPhysicsContactInfo = (PhysicsContactInfo*) i_event->getUserData();
    if ( pPhysicsContactInfo && pPhysicsContactInfo->m_entityHandle == m_entityHandle && pPhysicsContactInfo->m_otherShape )
    {
        if ( pPhysicsContactInfo->m_otherEntityHandle != m_ownerHandle )
        {
            HealthComponent* pHealthComponent = EntitySystem::GetInstance()->GetComponent<HealthComponent>( pPhysicsContactInfo->m_otherEntityHandle );
            if ( pHealthComponent )
            {
                pHealthComponent->ChangeHealth( -m_damage );
            }
            EventManager::GetInstance()->SendEvent( "MunitionContact", &m_ownerHandle );
        }
    }
}
