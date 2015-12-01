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
    
    std::string pSpritePath = std::string( i_dnaObject["Sprite"].GetString() );
    pSpritePath.insert( 0, "Baked/" );
    
    m_sprite = Sprite::create( pSpritePath );
    RenderSystem::m_layer->addChild( m_sprite );
}

RenderComponent::~RenderComponent()
{
    m_sprite->removeFromParent();
    m_sprite->cleanup();
    RenderSystem::UnregisterComponent( this );
}