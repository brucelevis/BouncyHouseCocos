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

RenderComponent::RenderComponent( EntityHandle i_entityHandle )
{
    m_entityHandle = i_entityHandle;
    
    std::cout << "Created a RenderComponent!" << std::endl;
    
    RenderSystem::RegisterComponent( this );
}

void RenderComponent::Init( Layer* i_layer )
{
    m_sprite = Sprite::create( "player.png" );
    m_sprite->setPosition( Vec2( 500.0f, 500.0f ) );
    i_layer->addChild( m_sprite );
}

RenderComponent::~RenderComponent()
{
    m_sprite->removeFromParent();
    m_sprite->cleanup();
    RenderSystem::UnregisterComponent( this );
}