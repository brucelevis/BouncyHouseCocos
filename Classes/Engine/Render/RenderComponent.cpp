//
//  RenderComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include "cocos2d.h"

#include "EffectSprite/EffectSprite.h"
#include "../Lighting/LightEffect.h"
#include "../Entity/EntitySystem.h"
#include "../Event/EventManager.h"
#include "RenderComponent.h"
#include "RenderSystem.h"
#include "../Physics/PhysicsComponent.h"

std::string RenderComponent::s_componentType = "RenderComponent";

void RenderComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    RenderSystem::GetInstance()->RegisterComponent( this );
    m_scale = 1.0f;
    m_zOrder = 0;
    
    if ( i_dnaObject.HasMember( "DefaultSprite" ) )
    {
        m_defaultSpriteName = i_dnaObject["DefaultSprite"].GetString();
    }
    if ( i_dnaObject.HasMember( "FacingLeft" ) )
    {
        m_facingLeft = i_dnaObject["FacingLeft"].GetBool();
    }
    
    if ( i_dnaObject.HasMember( "ZOrder" ) )
    {
        m_zOrder = i_dnaObject["ZOrder"].GetInt();
    }
    
    if ( i_dnaObject.HasMember( "Sprite" ) )
    {
        m_spriteName = i_dnaObject["Sprite"].GetString();
    }
    if ( i_dnaObject.HasMember( "SpriteSheet" ) )
    {
        m_spriteSheetName = i_dnaObject["SpriteSheet"].GetString();
    }
    
    if ( i_dnaObject.HasMember( "Scale" ) )
    {
        m_scale = i_dnaObject["Scale"].GetDouble();
    }
}

void RenderComponent::OnActivate()
{
    if ( !m_spriteName.empty() )
    {
        std::string pSpritePath = std::string( m_spriteName );
        pSpritePath.insert( 0, "Baked/" );
        
        m_sprite = EffectSprite::create( pSpritePath );
        
        PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
        if ( pPhysicsComponent && pPhysicsComponent->GetNode() )
        {
            
            m_sprite->setAnchorPoint( pPhysicsComponent->GetAnchorPoint() );
            pPhysicsComponent->GetNode()->addChild( m_sprite );
            pPhysicsComponent->GetNode()->setZOrder( m_zOrder );
            m_sprite->setPosition( cocos2d::Vec2( pPhysicsComponent->GetWidth() * pPhysicsComponent->GetAnchorPoint().x, pPhysicsComponent->GetHeight() * pPhysicsComponent->GetAnchorPoint().y ) );
        }
    }
    else if ( !m_spriteSheetName.empty() )
    {
        std::string pSpriteSheetPath = std::string( m_spriteSheetName );
        pSpriteSheetPath.insert( 0, "Baked/" );
        pSpriteSheetPath.insert( pSpriteSheetPath.length(), ".png" );
        std::string pSpriteSheetPlistPath = std::string( m_spriteSheetName );
        pSpriteSheetPlistPath.insert( 0, "Baked/" );
        pSpriteSheetPlistPath.insert( pSpriteSheetPlistPath.length(), ".plist" );
        m_spriteSheetNormalPath = std::string( m_spriteSheetName );
        m_spriteSheetNormalPath.insert( 0, "Baked/" );
        m_spriteSheetNormalPath.insert( m_spriteSheetNormalPath.length(), "_n.png" );
        
        cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pSpriteSheetPlistPath );
        
        m_sprite = EffectSprite::createWithSpriteFrame( cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName( m_defaultSpriteName ) );
        m_sprite->setNormalMap( m_spriteSheetNormalPath );
        
        PhysicsComponent* pPhysicsComponent = EntitySystem::GetInstance()->GetComponent<PhysicsComponent>( m_entityHandle );
        if ( pPhysicsComponent && pPhysicsComponent->GetNode() )
        {
            m_sprite->setAnchorPoint( pPhysicsComponent->GetAnchorPoint() );
            pPhysicsComponent->GetNode()->addChild( m_sprite );
            pPhysicsComponent->GetNode()->setZOrder( m_zOrder );
            m_sprite->setPosition( cocos2d::Vec2( pPhysicsComponent->GetWidth() * pPhysicsComponent->GetAnchorPoint().x, pPhysicsComponent->GetHeight() * pPhysicsComponent->GetAnchorPoint().y ) );
        }
    }
    
    if ( m_sprite )
    {
        m_sprite->setTag( m_entityHandle );
        if ( m_scale != 0.0f )
        {
            m_sprite->setScale( m_scale );
        }
        
        if ( m_facingLeft )
        {
            m_sprite->setScale( m_scale * -1.0f, m_scale );
        }
    }
}

RenderComponent::~RenderComponent()
{
    m_sprite->removeFromParent();
    RenderSystem::GetInstance()->UnregisterComponent( this );
}

float RenderComponent::GetScale()
{
    return m_scale;
}

void RenderComponent::SetScale( float i_scale )
{
    m_scale = i_scale;
    if ( m_sprite )
    {
        m_sprite->setScale( i_scale );
    }
}
