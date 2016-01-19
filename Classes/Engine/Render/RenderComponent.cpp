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
#include "../Event/EventManager.h"
#include "RenderComponent.h"
#include "RenderSystem.h"

std::string RenderComponent::s_componentType = "RenderComponent";

void RenderComponent::DNADataInit( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    RenderSystem::GetInstance()->RegisterComponent( this );
    
    if ( i_dnaObject.HasMember( "FacingLeft" ) )
    {
        m_facingLeft = i_dnaObject["FacingLeft"].GetBool();
    }
    
    int pZOrder = 0;
    if ( i_dnaObject.HasMember( "ZOrder" ) )
    {
        pZOrder = i_dnaObject["ZOrder"].GetInt();
    }
    
    if ( i_dnaObject.HasMember( "Sprite" ) )
    {
        std::string pSpritePath = std::string( i_dnaObject["Sprite"].GetString() );
        pSpritePath.insert( 0, "Baked/" );
        
        m_sprite = EffectSprite::create( pSpritePath );
        RenderSystem::GetInstance()->GetScene()->addChild( m_sprite, pZOrder );
    }
    else if ( i_dnaObject.HasMember( "SpriteSheet" ) )
    {
        m_spriteSheetName = i_dnaObject["SpriteSheet"].GetString();
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
        
        m_sprite = EffectSprite::createWithSpriteFrame( cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName( i_dnaObject["DefaultSprite"].GetString() ) );
        m_sprite->setNormalMap( m_spriteSheetNormalPath );
        RenderSystem::GetInstance()->GetScene()->addChild( m_sprite, pZOrder );
    }
    SetFacing( RenderComponent::FacingDirection::LEFT );
    m_sprite->setTag( i_entityHandle );
}

RenderComponent::~RenderComponent()
{
    m_sprite->removeFromParent();
    RenderSystem::GetInstance()->UnregisterComponent( this );
}

RenderComponent::FacingDirection RenderComponent::GetFacing()
{
    FacingDirection pFacing = FacingDirection::NONE;
    if ( m_sprite )
    {
        float pScaleX = m_sprite->getScaleX();
        if ( ( pScaleX < 0.0f && !m_facingLeft ) || ( pScaleX > 0.0f && m_facingLeft ) )
        {
            return FacingDirection::LEFT;
        }
        else if ( ( pScaleX > 0.0f && !m_facingLeft ) || ( pScaleX < 0.0f && m_facingLeft ) )
        {
            return FacingDirection::RIGHT;
        }
    }
    return pFacing;
}

bool RenderComponent::SetFacing( FacingDirection i_facingDirection )
{
    float pScaleX = m_sprite->getScaleX();
    switch ( i_facingDirection )
    {
        case FacingDirection::LEFT:
            pScaleX = -1.0f * fabs( pScaleX );
            break;
        case FacingDirection::RIGHT:
            pScaleX = 1.0f * fabs( pScaleX );
            break;
        default:
            break;
    }
    if ( m_facingLeft )
    {
        pScaleX *= -1.0f;
    }
    if ( m_sprite )
    {
        if ( m_sprite->getScaleX() != pScaleX )
        {
#ifdef DEBUG_NAN
            ASSERTS( !isnan( pScaleX ), "NaN entering RenderSystem!" );
#endif
            m_sprite->setScaleX( pScaleX );
            EventManager::GetInstance()->SendEvent( "FacingChanged", &m_entityHandle );
        }
        return true;
    }
    return false;
}
