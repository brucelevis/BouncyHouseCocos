//
//  RenderComponent.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include <iostream>

#include "RenderComponent.h"
#include "RenderSystem.h"

using namespace cocos2d;

std::string RenderComponent::s_componentType = "RenderComponent";

void RenderComponent::Init( EntityHandle i_entityHandle, const rapidjson::Value& i_dnaObject )
{
    m_entityHandle = i_entityHandle;
    RenderSystem::RegisterComponent( this );
    
    if ( i_dnaObject.HasMember( "Sprite" ) )
    {
        std::string pSpritePath = std::string( i_dnaObject["Sprite"].GetString() );
        pSpritePath.insert( 0, "Baked/" );
        
        m_sprite = Sprite::create( pSpritePath );
        RenderSystem::m_activeScene->addChild( m_sprite );
    }
    else if ( i_dnaObject.HasMember( "SpriteSheet" ) )
    {
        std::string pSpriteSheetPath = std::string( i_dnaObject["SpriteSheet"].GetString() );
        pSpriteSheetPath.insert( 0, "Baked/" );
        pSpriteSheetPath.insert( pSpriteSheetPath.length(), ".png" );
        std::string pSpriteSheetPlistPath = std::string( i_dnaObject["SpriteSheet"].GetString() );
        pSpriteSheetPlistPath.insert( 0, "Baked/" );
        pSpriteSheetPlistPath.insert( pSpriteSheetPlistPath.length(), ".plist" );
        
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile( pSpriteSheetPlistPath );
        m_spriteBatchNode = SpriteBatchNode::create( pSpriteSheetPath );
        
        // TODO: How do we find this frame name automagically?
        m_sprite = Sprite::createWithSpriteFrameName( "Vik1_Run_00.png" );
        m_spriteBatchNode->addChild( m_sprite );
        
        RenderSystem::m_activeScene->addChild( m_spriteBatchNode );
    }
}

RenderComponent::~RenderComponent()
{
    m_sprite->removeFromParent();
    m_sprite->cleanup();
    RenderSystem::UnregisterComponent( this );
}

RenderComponent::FacingDirection RenderComponent::GetFacing()
{
    FacingDirection pFacing = FacingDirection::NONE;
    if ( m_sprite )
    {
        float pScaleX = m_sprite->getScaleX();
        if ( pScaleX == -1.0f )
        {
            return FacingDirection::LEFT;
        }
        else if ( pScaleX == 1.0f )
        {
            return FacingDirection::RIGHT;
        }
    }
    return pFacing;
}

bool RenderComponent::SetFacing( FacingDirection i_facingDirection )
{
    float pScaleX = 0.0f;
    switch ( i_facingDirection )
    {
        case FacingDirection::LEFT:
            pScaleX = 1.0f;
            break;
        case FacingDirection::RIGHT:
            pScaleX = -1.0f;
            break;
        default:
            break;
    }
    if ( m_sprite )
    {
        m_sprite->setScaleX( pScaleX );
        return true;
    }
    return false;
}