//
//  LightingComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 12/8/15.
//
//

#include "LightingComponent.h"
#include "LightingSystem.h"
#include "../Entity/EntitySystem.h"
#include "../Physics/PhysicsComponent.h"

std::string LightingComponent::s_componentType = "LightingComponent";

void LightingComponent::Init( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
}

void LightingComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    
}

LightingComponent::~LightingComponent()
{
    if ( m_lightEffect )
    {
        m_lightEffect->release();
    }
}

void LightingComponent::OnActivate()
{
    LightingSystem::RegisterComponent( this );
}

void LightingComponent::OnDeactivate()
{
    LightingSystem::UnregisterComponent( this );
}

void LightingComponent::Update( float i_dt )
{
    PhysicsComponent* pPhysicsComponent = EntitySystem::GetComponent<PhysicsComponent>( m_entityHandle );
    if ( pPhysicsComponent )
    {
        cocos2d::Vec3 pPosition = cocos2d::Vec3( pPhysicsComponent->GetPosition().x, pPhysicsComponent->GetPosition().y, 0.0f );
        cocos2d::Vec3 pLightPosition = pPosition + m_offset;
        m_lightEffect->setLightPos( pPosition + m_offset );
    }
}

void LightingComponent::SetLightEffect( cocos2d::Vec3 i_offset, float i_brightness, cocos2d::Color3B i_color, float i_radius, float i_halfRadius )
{
    m_offset = i_offset;
    
    m_lightEffect = LightEffect::create();
    m_lightEffect->retain();
    m_lightEffect->setBrightness( i_brightness );
    m_lightEffect->setLightColor( i_color );
    m_lightEffect->setLightCutoffRadius( i_radius );
    m_lightEffect->setLightHalfRadius( i_halfRadius );
    LightingSystem::AddLightEffect( m_lightEffect );
}
