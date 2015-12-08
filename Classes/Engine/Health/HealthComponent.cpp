//
//  HealthComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/5/15.
//
//
#include <string>

#include "cocos2d.h"

#include "../Animation/AnimationComponent.h"
#include "../Entity/EntitySystem.h"
#include "HealthComponent.h"
#include "HealthSystem.h"
#include "../Render/RenderComponent.h"
#include "../Render/RenderSystem.h"

std::string HealthComponent::s_componentType = "HealthComponent";

void HealthComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    
    m_health = 0.0f;
    m_maxHealth = 0.0f;
    
    if ( i_dnaObject.HasMember( "MaxHealth" ) )
    {
        m_maxHealth = i_dnaObject["MaxHealth"].GetDouble();
    }
}

HealthComponent::~HealthComponent()
{
    
}

void HealthComponent::OnActivate()
{
    HealthSystem::RegisterComponent( this );
    m_health = m_maxHealth;
    m_dying = false;
}

void HealthComponent::OnDeactivate()
{
    HealthSystem::UnregisterComponent( this );
}

void HealthComponent::BeginDeath()
{
    if ( !m_dying )
    {
        m_dying = true;
        cocos2d::EventCustom event( "EntityDeath" );
        event.setUserData( &m_entityHandle );
        RenderSystem::m_activeScene->GetEventDispatcher()->dispatchEvent( &event );
        
//        AnimationComponent* pAnimationComponent = EntitySystem::GetComponent<AnimationComponent>( m_entityHandle );
//        if ( pAnimationComponent )
//        {
//            auto pCallback = CallFunc::create( CC_CALLBACK_0( HealthComponent::DeathComplete, this ) );
//            pAnimationComponent->StartMotion( "Death", 1, pCallback );
//        }
//        else
//        {
            DeathComplete();
            m_dying = true;
//        }
    }
}

void HealthComponent::DeathComplete()
{
    EntitySystem::MarkForDelete( m_entityHandle );
}