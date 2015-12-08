//
//  RenderSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 11/28/15.
//
//

#include <iostream>
#include "RenderSystem.h"

std::map<EntityHandle, Component*> RenderSystem::m_components;
GameScene* RenderSystem::m_activeScene;

void RenderSystem::RegisterComponent( Component* i_component )
{
    m_components.insert( std::make_pair( i_component->m_entityHandle, i_component ) );
}

void RenderSystem::UnregisterComponent( Component* i_component )
{
    m_components.erase( i_component->m_entityHandle );
}

void RenderSystem::Update( float i_dt )
{
#ifdef DEBUG
    DebugUpdate( i_dt );
#endif
}

#ifdef DEBUG
void RenderSystem::DebugDraw( cocos2d::DrawNode* i_drawNode, float i_duration )
{
    i_drawNode->runAction( cocos2d::Sequence::create( cocos2d::DelayTime::create( i_duration ), cocos2d::RemoveSelf::create(), nullptr ) );
    RenderSystem::m_activeScene->addChild( i_drawNode, 2000 );
}

void RenderSystem::DebugText( std::string i_text, cocos2d::Vec2 i_position, float i_duration, cocos2d::Color4F i_color, int i_fontSize, cocos2d::TextHAlignment i_hAlignment )
{
    cocos2d::Label* pLabel = cocos2d::Label::createWithSystemFont( i_text, "Courier", i_fontSize );
    pLabel->setPosition( i_position );
    pLabel->setTextColor( cocos2d::Color4B( i_color ) );
    pLabel->setAlignment( i_hAlignment );
    pLabel->runAction( cocos2d::Sequence::create( cocos2d::DelayTime::create( i_duration ), cocos2d::RemoveSelf::create(), nullptr ) );
    
    m_activeScene->addChild( pLabel, 2000 );
}

void RenderSystem::DebugUpdate( float i_dt )
{

}
#endif