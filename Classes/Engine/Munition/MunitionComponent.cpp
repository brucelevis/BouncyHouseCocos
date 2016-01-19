//
//  MunitionComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/15/16.
//
//

#include "MunitionComponent.h"
#include "cocos2d.h"

#include "../AI/AIComponent.h"
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
    m_damage = 0;
    m_hitOnce = true;
    MunitionSystem::GetInstance()->RegisterComponent( this );
    
    if ( i_dnaObject.HasMember( "Damage" ) )
    {
        m_damage = i_dnaObject["Damage"].GetDouble();
    }
    if ( i_dnaObject.HasMember( "InflictState" ) )
    {
        m_inflictState = i_dnaObject["InflictState"].GetString();
    }
    if ( i_dnaObject.HasMember( "HitOnce" ) )
    {
        m_hitOnce = i_dnaObject["HitOnce"].GetBool();
    }
    
    EventManager::GetInstance()->RegisterForEvent( "RemovingEntity", CC_CALLBACK_1( MunitionComponent::OnRemovingEntityEvent, this ), this );
}

void MunitionComponent::OnActivate()
{
    EventManager::GetInstance()->RegisterForEvent( "PhysicsContactBegin", CC_CALLBACK_1( MunitionComponent::OnPhysicsContactBeginEvent, this ), this );
    EventManager::GetInstance()->RegisterForEvent( "FacingChanged", CC_CALLBACK_1( MunitionComponent::OnFacingChangedEvent, this ), this );
}

void MunitionComponent::OnDeactivate()
{
    EventManager::GetInstance()->UnregisterForEvent( "PhysicsContactBegin", this );
    EventManager::GetInstance()->UnregisterForEvent( "FacingChanged", this );
}

MunitionComponent::~MunitionComponent()
{
    MunitionSystem::GetInstance()->UnregisterComponent( this );
    
    EventManager::GetInstance()->UnregisterForEvent( "RemovingEntity", this );
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
            
            if ( pOPC->GetNode()->getScaleX() < 0.0f )
            {
                cocos2d::Vec2 pOffset = pPC->GetPositionOffset();
                pOffset.x *= -1.0f;
                pPC->SetPositionOffset( pOffset );
            }
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
            if ( !m_hitOnce || std::find( m_hitEntities.begin(), m_hitEntities.end(), pPhysicsContactInfo->m_otherEntityHandle ) == m_hitEntities.end() )
            {
                m_hitEntities.push_back( pPhysicsContactInfo->m_otherEntityHandle );
                HealthComponent* pHealthComponent = EntitySystem::GetInstance()->GetComponent<HealthComponent>( pPhysicsContactInfo->m_otherEntityHandle );
                if ( pHealthComponent )
                {
                    pHealthComponent->ChangeHealth( -m_damage );
                }
                
                if ( strcmp( m_inflictState.c_str(), "" ) != 0 )
                {
                    AIComponent* pAIComponent = EntitySystem::GetInstance()->GetComponent<AIComponent>( pPhysicsContactInfo->m_otherEntityHandle );
                    if ( pAIComponent && pAIComponent->GetBrain() )
                    {
                        pAIComponent->GetBrain()->PushState( m_inflictState );
                    }
                }
                
                
                EventManager::GetInstance()->SendEvent( "MunitionContact", &m_ownerHandle );
            }
        }
    }
}

void MunitionComponent::OnRemovingEntityEvent( cocos2d::EventCustom* i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( pEntityHandle == m_ownerHandle )
    {
        EntitySystem::GetInstance()->MarkForDelete( m_entityHandle );
    }
}


void MunitionComponent::OnFacingChangedEvent( cocos2d::EventCustom* i_event )
{
    EntityHandle pEntityHandle = *((int*)(i_event->getUserData()));
    if ( pEntityHandle == m_ownerHandle )
    {
        PhysicsComponent* pPC = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
        if ( pPC )
        {
            cocos2d::Vec2 pOffset = pPC->GetPositionOffset();
            pOffset.x *= -1.0f;
            pPC->SetPositionOffset( pOffset );
        }
    }
}
