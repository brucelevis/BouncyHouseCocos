//
//  DebugDrawSystem.cpp
//  BouncyHouse
//
//  Created by Derek Peterson on 1/13/16.
//
//

#include <iostream>
#include "DebugDrawSystem.h"
#include "RenderSystem.h"

DebugDrawSystem* DebugDrawSystem::s_instance;

DebugDrawSystem* DebugDrawSystem::GetInstance()
{
    if ( !s_instance )
    {
        s_instance = new DebugDrawSystem();
    }
    return s_instance;
}

void DebugDrawSystem::DestroyInstance()
{
    if ( s_instance )
    {
        delete s_instance;
        s_instance = NULL;
    }
}

void DebugDrawSystem::Update( float i_dt )
{

}


void DebugDrawSystem::DebugDraw( cocos2d::DrawNode* i_drawNode, float i_duration )
{
    i_drawNode->runAction( cocos2d::Sequence::create( cocos2d::DelayTime::create( i_duration ), cocos2d::RemoveSelf::create(), nullptr ) );
    RenderSystem::GetInstance()->GetScene()->addChild( i_drawNode, 2000 );
}

void DebugDrawSystem::DebugText( std::string i_text, cocos2d::Vec2 i_position, float i_duration, cocos2d::Color4F i_color, int i_fontSize, cocos2d::TextHAlignment i_hAlignment )
{
    cocos2d::Label* pLabel = cocos2d::Label::createWithSystemFont( i_text, "Courier", i_fontSize );
    pLabel->setPosition( i_position );
    pLabel->setTextColor( cocos2d::Color4B( i_color ) );
    pLabel->setAlignment( i_hAlignment );
    pLabel->runAction( cocos2d::Sequence::create( cocos2d::DelayTime::create( i_duration ), cocos2d::RemoveSelf::create(), nullptr ) );
    
    RenderSystem::GetInstance()->GetScene()->addChild( pLabel, 2000 );
}
